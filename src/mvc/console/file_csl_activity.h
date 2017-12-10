//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_FILECONSOLE_H
#define DIFFUSION_FILECONSOLE_H

#include <mutex>
#include <thread>
#include <condition_variable>
#include "ConsoleActivity.h"
#include "../../module/cmds/options.h"
#include "../../tool/converter.h"
#include "../../module/cmds/cmds.h"
#include "../../cipher/Scheduler.h"
#include "../../cipher/items.h"
#include "../../tool/file_handler.h"

namespace lc{
    class FileConsoleActivity : public CipherConsoleActivity {
        int refreshTime = 100;
        int counter = 0;
        int itemCount = 0;
        FileOption option;
        Coord newest;
        std::thread* worker = nullptr;
        std::mutex lock;
        std::mutex notify;
        std::condition_variable condition;
    public:
        FileConsoleActivity(Console& console) : CipherConsoleActivity(console) {
            //@formatter:off
            M["-i"]         = EMPTY_STRING;
            M["-o"]         = EMPTY_STRING;
            M["-op"]        = EMPTY_STRING;
            //@formatter:on
        }

    protected:
        void initialize() throw(DiffusionException) {
            CipherConsoleActivity::initialize();
            addNotifier("scheduler.begin", &notifier_scheduler_begin);
            addNotifier("scheduler.end", &notifier_scheduler_end);
            addNotifier("scheduler.abort", &notifier_scheduler_abort);
            addNotifier("CI.file.begin", &notifier_cip_begin);
            addNotifier("CI.file.end", &notifier_cip_end);
            addNotifier("CI.item.error", &notifier_item_error);
            addNotifier("CI.item.completed", &notifier_item_complete);
        }

        std::string getTipLine() {
            return I18N->get(TIP_LINE_FILE);
        }

        Validator* validate(int code) override {
            Validator* vr = CipherConsoleActivity::validate(code);
            std::string& in = M["-i"];
            if (in.length() == 0) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_FI_MISS, in.c_str()));
            } else if (FH::find_file(in, option.isdir_in) == -1) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_FL_NFD, in.c_str()));
            }
            std::string& ops = M["-op"];
            bool dos = ops.find(C_DO_SOURCE) != -1;
            if (dos) {
                vr = vr->append(vdr::WARNING_HEIGH, I18N->gf(VDR_OPS_DOS, ops.c_str()));
            }
            if (dos && ops.find(C_DELETE_SOURCE) != -1) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_OPS_DD, ops.c_str()));
            }
            if (dos && ops.find(C_PADDING) != -1) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_OPS_DP, ops.c_str()));
            }
            if (!dos && M["-o"] == EMPTY_STRING) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_FO_MISS));
            }
            std::string out = T::get_output(M["-o"], option.isdir_out);
            if (!dos && !option.isdir_in && !option.isdir_out && in == out) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_FIO_EQUAL, M["-o"].c_str()));
            }
            int fileSmashTimes = T::get_fileSmashTimes(ops);
            if (fileSmashTimes > MAX_SMASH_TIMES) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_FST_TOOB, MAX_SMASH_TIMES, fileSmashTimes));
            } else if (fileSmashTimes < MIN_SMASH_TIMES) {
                vr = vr->append(vdr::WARNING, I18N->gf(VDR_FST_TOOS, MIN_SMASH_TIMES, fileSmashTimes));
            }
            std::string filter = T::cvt_regex(M["-f"]);
            if (filter != NON && !Strings::test_reg(filter)) {
                vr = vr->append(vdr::INVALID, I18N->gf(VDR_REG_INC, filter.c_str()));
            }
            option.fileSmashTimes = fileSmashTimes;
            return vr;
        }

        bool execute(CipherOption* option, int code) throw(DiffusionException) {
            FileOption* fo = new FileOption();
            if (CipherConsoleActivity::execute(fo, code)) {
                fo->fileSmashTimes = this->option.fileSmashTimes;
                fo->isdir_in = this->option.isdir_in;
                T::write_options(M["-op"], fo->options);
                fo->filter = T::cvt_regex(M["-f"]);
                fo->options |= code;
                fo->input = T::erase_remend(M["-i"]);
                fo->output = T::get_output(M["-o"], fo->isdir_out);
                fo->options |= (CORE_COUNT_LOG > 1) ? CO::MULTICORE : 0;
                invoke(cmd::FILE_CIPHER, fo);
            }
        }

        void update_progress(Item* item, Coord coord) {
            BufferContact& c = item->contact;
            int w = (int) console.getWindowSize(Console::WIDTH);;
            double value;
            uint64 time;
            char buf[] = "[${t+,HH:mm:ss}] ${%5.2f%%}";
            std::string format;
            do {
                lock.lock();
                value = (1.0 * c.done / c.length) * 100;
                console.setCoord(coord);
                format.clear();
                format.append(buf);
                time = getSystemTime() - item->start;
                Messages::format(format, &time, value);
                console.out(format, Color::THIN_SH_GREEN);
                lock.unlock();
                if (contains_any(item->status(), Item::ONERROR | Item::COMPLETED)) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(refreshTime));
                if (c.done == c.length) {
                    break;
                }
                if (refreshTime < 1000) {
                    refreshTime = 1000;
                }
            } while (c.done < c.length);
            lock.lock();
            console.setCoord(coord);
            if (format.length() > 6) {
                format.erase(format.length() - 6, 6);
            }
            bool error = contains(item->flags(), Item::ONERROR);
            format.append(error ? "  ERROR" : "  100%");
            console.out(format, error ? Color::THIN_RED : Color::GREEN);
            if (++counter == itemCount) {
                condition.notify_all();
            }
            lock.unlock();
        }

        void begin_progress(Item* item, Coord coord) {
            worker = new std::thread(update_progress, this, item, coord);
            worker = nullptr;
        }

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Notifiers

        Notifier notifier_scheduler_begin = [this](NotifyEvent& event) {
            SchedulerContact& sc = *(SchedulerContact*) event.getAttachment();
            counter = 0;
            itemCount = sc.fileCount;
            lock.lock();
            console.out(I18N->gf(CIPHER_SCHEDULER_BEGIN, sc.fileCount), Color::WHILE);
            console << "\n\n";
            console.setCursorVisible(false);
            newest = console.getCoord();
            lock.unlock();
        };
        Notifier notifier_scheduler_abort = [this](NotifyEvent& event) {
            condition.notify_all();
        };

        Notifier notifier_scheduler_end = [this](NotifyEvent& event) {
            SchedulerContact& sc = *(SchedulerContact*) event.getAttachment();
            if (counter != itemCount && sc.status != Scheduler<void*>::ABORT) {
                std::unique_lock<std::mutex> lck(notify);
                condition.wait(lck);
            }
            lock.lock();
            console.setCoord(newest);
            console.out(I18N->gf(CIPHER_SCHEDULER_END, &sc.time), Color::WHILE);
            console << "\n";
            console.setCursorVisible(true);
            newest = console.getCoord();
            lock.unlock();
        };
        Notifier notifier_item_error = [this](NotifyEvent& event) {
            Item& item = *(Item*) event.getAttachment();
            item.flags(Item::NOTIFIED);
            lock.lock();
            console.setCoord(newest);
            console << "\n";
            console.out(I18N->gf(CIPHER_ITEM_ERROR, item.message.c_str()), Color::THIN_RED);
            console << "\n";
            console.out(I18N->gf(TIP_ITEM_ERROR, item.message.c_str()), Color::THIN_YELLOW);
            console.setCursorVisible(true);
            int get = console.in().get();
            console.clear(Console::SIN);
            console.sync(Console::SIN);
            int* code = new int;
            if (get == 'y' || get == 'Y') {
                *code = 0;
            } else if (get == '*') {
                *code = 1;
            } else if (get == 'n' || get == 'N') {
                *code = -1;
            }
            console.setCursorVisible(false);
            newest = console.getCoord();
            lock.unlock();
            event.setAttachment(code);
        };
        Notifier notifier_cip_begin = [this](NotifyEvent& event) {
            Item& item = *(Item*) event.getAttachment();
            SchedulerContact& sc = *item.scheduler;
            lock.lock();
            int w = (int) console.getWindowSize(Console::WIDTH);
            std::string& file = item.in_file;
            std::string output = I18N->gf(CIPHER_FILE_BEGIN, file.c_str(), &item.length, sc.done, sc.fileCount);
            fill(output, w, 25);
            console.setCoord(newest);
            console.out(output, Color::THIN_SH_GREEN);
            Coord get = console.getCoord();
            console.out("\n");
            newest = console.getCoord();
            begin_progress(&item, get);
            lock.unlock();
        };
        Notifier notifier_cip_end = [this](NotifyEvent& event) {
            Item& item = *(Item*) event.getAttachment();
            lock.lock();
            uint64 time = item.end - item.start;
            std::string& outfile = item.out_file;
            console.setCoord(newest);
            console.out(I18N->gf(CIPHER_FILE_END, outfile.c_str(), &item.length, &time), Color::SH_GREEN);
            console << "\n";
            newest = console.getCoord();
            lock.unlock();
        };

        Notifier notifier_item_complete = [this](NotifyEvent& event) {
            Item& item = *(Item*) event.getAttachment();
            uint64 time = item.end - item.start;
            lock.lock();
            console.setCoord(newest);
            if (contains(item.flags(), Item::WITH_ERROR, Item::NOTIFIED)) {
                console.out(I18N->gf(CIPHER_ITEM_ERROR, item.message.c_str()), Color::THIN_RED);
                console << "\n";
            }
            console.out(I18N->gf(CIPHER_ITEM_COMPETED, &time), Color::THIN_SH_GREEN);
            console << "\n";
            newest = console.getCoord();
            lock.unlock();
        };
    };
}
#endif //DIFFUSION_FILECONSOLE_H
