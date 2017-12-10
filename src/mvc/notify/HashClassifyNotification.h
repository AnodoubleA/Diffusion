//
// Created by Alice on 2017.02.27.
//
#pragma once
#ifndef DIFFUSION_HASHCLASSIFYNOTIFICATION_H
#define DIFFUSION_HASHCLASSIFYNOTIFICATION_H

#include <string>
#include <map>
#include <list>
#include "Notifier.h"
#include "ClassifyNotification.h"
#include "../../tool/Strings.h"
#include <regex>

namespace lc {

    class HashClassifyNotification : public ClassifyNotification {

    protected:
        std::map<std::string, std::list<Notifier*>> content;

    public:
        ~HashClassifyNotification() = default {
            content.clear();
        }

        void notify(NotifyEvent& event) {
            std::string& name(const_cast<std::string&>(event.getName()));
            std::map<std::string, std::list<Notifier*>>::iterator it;
            for (it = content.begin(); it != content.end(); it++) {
                std::string key = const_cast<std::string&>(it->first);
                if (event.isLimited()) {
                    key = Strings::replaceAll(key, "*", "\\*");
                } else {
                    key = Strings::replaceAll(key, "*", ".+?");
                }
                if (Strings::match(name, key)) {
                    notify(it->second, event);
                }
            }
        }

        void addNotifier(const std::string& name, Notifier notifier) {
            addNotifier(name, &notifier);
        }

        void addNotifier(const std::string& name, Notifier* notifier) {
            std::map<std::string, std::list<Notifier*>>::iterator it = content.find(name);
            if (it == content.end()) {
                std::list<Notifier*> _list;
                _list.push_back(notifier);
                content[name] = _list;
            } else {
                it->second.push_back(notifier);
            }
        }

    protected:
        void notify(std::list<Notifier*>& ls, NotifyEvent& event) {
            for (Notifier* notifier : ls) {
                notify(event, *notifier);
            }
        }

        void notify(NotifyEvent& event, Notifier& notifier) {
            notifier(event);
        }
    };
}
#endif //DIFFUSION_HASHCLASSIFYNOTIFICATION_H
