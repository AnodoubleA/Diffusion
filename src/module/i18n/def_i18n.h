//
// Created by Alice on 2017.03.10.
//
#pragma once
#ifndef DIFFUSION_DEF_I18N_H
#define DIFFUSION_DEF_I18N_H

#include "../config/Config.h"
#include "../format/format.h"
#include "lang.h"

namespace lc{
    class DefaultI18N : public AbstractI18N {
    public:
        void load(const std::string& lang, Internationalization* def = nullptr) override {
            //@formatter:off
            content[ERROR_FILE_OPEN]                  = "Open file error: ${%s}";
            content[ERROR_FILE_CREATE]                = "Create file error: ${%s}";
            content[ERROR_FILE_READ]                  = "Read file error: ${%s}";
            content[ERROR_FILE_WRITE]                 = "Write file error: ${%s}";
            content[ERROR_FILE_RENAME]                = "Rename file failed, code: [${%d}]. At: ${%s}";
            content[ERROR_DIR_CREATE]                 = "Create directory error: ${%s}";
            content[ERROR_FILE_FORMAT_INC]            = "Incorrect file format, may not encipher by this application: ${%s}";
            content[ERROR_FILE_SIZE_INC]              = "Incorrect group size [${%d}] in file: ${%s}";
            content[ERROR_FILE_HVS_USP]               = "Un-support file version [${%d}] in file: ${%s}";
            content[ERROR_FILE_AVS_USP]               = "Un-support algorithm version [${%d}] in file: ${%s}";
            content[ERROR_FILE_KVS_USP]               = "Un-support key version [${%d}] in file: ${%s}";
            content[ERROR_FILE_LEN_INC]               = "Incorrect file data-length: ${%s}";
            content[ERROR_FILE_OMISS_WPAD]            = "Miss out-file(or out directory) because source-file have padding: ${%s}";
            content[ERROR_FILE_OMISS_WCOV]            = "In cover option but not do-source, out-file cannot be equal input file: ${%s}";
            content[ERROR_FILE_DOS_PAD]               = "Cannot do-source because source-file have padding: ${%s}";
            content[ERROR_TEXT_FORMAT_INC]            = "Wrong decipher text, may not encipher by this application.";
            content[ERROR_TEXT_SIZE_INC]              = "Wrong group size in text: ${%d}.";
            content[ERROR_TEXT_HVS_USP]               = "Un-support text version :${%d}.";
            content[ERROR_TEXT_AVS_USP]               = "Un-support algorithm version: ${%d}.";
            content[ERROR_TEXT_KVS_USP]               = "Un-support key version: ${%d}.";
            content[ERROR_TEXT_LEN_INC]               = "Incorrect text data-length: [${%d}].";
            content[ERROR_AVS_USP]                    = "Un-support  algorithm version: [${%d}].";
            content[ERROR_KVS_USP]                    = "Un-support  key version: [${%d}].";
            content[ERROR_KLV_USP]                    = "Un-support  key level: [${%d}].";
            content[ERROR_CFG_BUFMLT_OOR]             = "Value of [buffer.multiple] must be in range(${%d} ~ ${%d}), got: ${%d}";
            content[ERROR_FORMAT_EXPR]                = "Incorrect format expression , must like ${index,type,options}, at index <${%d}> in <${%d}>.";
            content[ERROR_FORMATTER_UNKNOWN]          = "Formatter is unknown: ${%s}.";

            content[WARN_LANG_FILE_NOT_FOUND]         = "Language file not found: ${%s}";
            content[WARN_LANG_FILE_READ]              = "Read language file error: ${%s}";

            content[TIP_ERROR]                        = "Error: ${%s}";
            content[TIP_ITEM_ERROR]                   = "Input <Y> to continue, <*> not show this again, <N> abort: ";
            content[TIP_CMD_UNKNOWN]                  = "Unknown command: ${%s}";
            content[TIP_OPS_UNKNOWN]                  = "Unknown option: ${%s}";
            content[TIP_LINE_MAIN]                    = "Input command>";
            content[TIP_LINE_TEXT]                    = "Text cipher>";
            content[TIP_LINE_FILE]                    = "File cipher>";
            content[TIP_LINE_SHOW_NAME]               = "Name";
            content[TIP_LINE_SHOW_VALUE]              = "Value";
            content[TIP_LINE_HELP_NAME]               = "Options";
            content[TIP_LINE_HELP_VALUE]              = "Description";
            content[TIP_LINE_VD_WARNING]              = "If you want to ignore those warning, input <Y> to continue: ";
            content[TIP_LINE_VD_WARNING_IMP]          = "If you want to ignore those warning, input <YES> to continue: ";

            content[HELP_OPS_M]                       = "[e|d] (e: encipher,d: decipher).";
            content[HELP_OPS_L]                       = "Cipher level [1-2].";
            content[HELP_OPS_S]                       = "Group size (default is 2048(bit), must be 2^N. In (256 ~ 524280).";
            content[HELP_OPS_I]                       = "Input (String: for <text>, file or directory: for <file>).";
            content[HELP_OPS_O]                       = "Output file(directory). If must be write in file, please start with \">\".";
            content[HELP_OPS_K]                       = "The key.";
            content[HELP_OPS_F]                       = "File filter.";
            content[HELP_OPS_KF]                      = "Key format[hex|base64|plain] for decode key, default is plain.";
            content[HELP_OPS_KFL]                     = "Key-file (file absolute path, if no file, set it to <non>. Use first).";
            content[HELP_OPS_OPS]                     = "Options [*|p|+|c].(*: Recursion, +: Do source file, p: Padding,c: Cover exists file).";
            content[HELP_OPS_WP]                      = "The space wrapper. Default is <\">";

            content[HELP_DRT_TEXT]                    = "Encipher(decipher) text.";
            content[HELP_DRT_FILE]                    = "Encipher(decipher) file(directory).";
            content[HELP_DRT_HELP]                    = "Print help.";
            content[HELP_DRT_SHOW]                    = "Show current options.";
            content[HELP_DRT_EXEC]                    = "Execute command, before this, command will never execute.";
            content[HELP_DRT_EXIT]                    = "Exit current command. At main command, this will exit program.";
            content[HELP_DRT_VALIDATE]                = "Validate options.";
            content[HELP_DRT_ENCIP]                   = "Execute encipher.";
            content[HELP_DRT_DECIP]                   = "Execute decipher.";

            content[VDR_TITLE_ERROR]                  = "Error: ";
            content[VDR_TITLE_WARNING]                = "Warning: ";
            content[VDR_TITLE_WARNING_IMP]            = "Warning( !Important ): ";
            content[VDR_GOOD]                         = "Very good!";
            content[VDR_MODE_UNKNOWN]                 = "Unknown mode for(-m): ${%s}.";
            content[VDR_TIN_MISS]                     = "You have not input any string for encipher(decipher) yet.";
            content[VDR_FI_MISS]                     = "You have not input any file(directory) to encipher(decipher) yet.";
            content[VDR_FO_MISS]                    = "You must be input output directory if not do-source.";
            content[VDR_FIO_EQUAL]                    = "Output cannot be equal input if not do-source: ${%s}";
            content[VDR_LEVEL_NAN]                    = "Level not an number: ${%s}.";
            content[VDR_LEVEL_OOR]                    = "Level out of range(${%d} ~ ${%d}), your is: ${%d}.";
            content[VDR_KF_INC]                       = "Unknown key format: ${%s}.";
            content[VDR_K_MISS]                       = "Need key or key-file.";
            content[VDR_K_SHORT]                      = "Key is too short, batter > ${%d}, your is: ${%d}.";
            content[VDR_KFL_NFD]                      = "Key-file not exists: ${%s}.";
            content[VDR_KFL_SHORT]                    = "Key-file is too short, batter > ${%d}.";
            content[VDR_KFL_INC]                      = "Key file must a file: ${%s}.";
            content[VDR_N_NAN]                        = "Group size not an number: ${%s}.";
            content[VDR_N_INC]                        = "Incorrect group size, must be 2^N (N=1,2,3...), input is: ${%d}";
            content[VDR_N_OOR]                        = "Group size out of range(${%d} ~ ${%d}), input is: ${%d}";
            content[VDR_OPS_DD]                       = "<+> and <x> definitely not exists at same time: ${%s}";
            content[VDR_OPS_DP]                       = "<+> and <p> definitely not exists at same time: ${%s}";
            content[VDR_FST_TOOB]                     = "File smash times is too big, must <= ${%d}. Got: ${%d}";
            content[VDR_FST_TOOS]                     = "File smash times is too small, batter >= ${%d}. Got: ${%d}.";
            content[VDR_FL_NFD]                       = "Input file(directory) not found from your input: ${%s}";
            content[VDR_REG_INC]                      = "Incorrect regexp expression: ${%s}";
            content[VDR_OPS_DOS]                      = "This is serious, because this option cannot be revoke: ${%s}";

            content[CIPHER_SCHEDULER_BEGIN]           = "File count: ${%d}, begin...";
            content[CIPHER_SCHEDULER_END]             = "Process completed. Total time [${t+,HH:mm:ss:SSS}]";
            content[CIPHER_TEXT_BEGIN]                = "";
            content[CIPHER_TEXT_END]                  = "OK>";
            content[CIPHER_FILE_BEGIN]                = " -> ${%s} [${d,%.3f}] [${%d}/${%d}]";
            content[CIPHER_FILE_END]                  = " => ${%s} [${d,%.3f}] [${t+,HH:mm:ss:SSS}]";
            content[CIPHER_DEL_BEGIN]                 = " X> ${%s} [${d,%.3f}]. Del...";
            content[CIPHER_DEL_END]                   = "\n Time ${t+,HH:mm:ss:SSS}.";
            content[CIPHER_ITEM_ERROR]                = "${%s}.";
            content[CIPHER_ITEM_COMPETED]             = "";


        }
    };
}
#endif //DIFFUSION_DEF_I18N_H
