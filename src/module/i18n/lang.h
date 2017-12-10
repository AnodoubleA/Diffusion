//
// Created by Angel on 2017/3/29.
//

#ifndef DIFFUSION_LANG_H
#define DIFFUSION_LANG_H
namespace lc{
    //@formatter:off
    static const char* ERROR_FILE_OPEN              = "error.file.open";
    static const char* ERROR_FILE_CREATE            = "error.file.create";
    static const char* ERROR_FILE_READ              = "error.file.read";
    static const char* ERROR_FILE_WRITE             = "error.file.write";
    static const char* ERROR_FILE_RENAME            = "error.file.rename";
    static const char* ERROR_DIR_CREATE             = "error.dir.create";
    static const char* ERROR_FILE_FORMAT_INC        = "error.file.format.inc";
    static const char* ERROR_FILE_SIZE_INC          = "error.file.size.inc";
    static const char* ERROR_FILE_HVS_USP           = "error.file.hvs.usp";     // un-support header version vs = version
    static const char* ERROR_FILE_AVS_USP           = "error.file.avs.usp";     // un-support algorithm version
    static const char* ERROR_FILE_KVS_USP           = "error.file.kvs.usp";     // un-support key version
    static const char* ERROR_FILE_LEN_INC           = "error.file.len.inc";     //
    static const char* ERROR_FILE_OMISS_WPAD        = "error.file.omiss.wpad";    //miss outfile with padding
    static const char* ERROR_FILE_OMISS_WCOV        = "error.file.omiss.wcov";    //miss outfile with padding
    static const char* ERROR_FILE_DOS_PAD           = "error.file.dos.pad";    //do-source & source have padding
    static const char* ERROR_TEXT_FORMAT_INC        = "error.text.format.inc";
    static const char* ERROR_TEXT_SIZE_INC          = "error.text.size.inc";
    static const char* ERROR_TEXT_HVS_USP           = "error.text.hvs.usp";     // un-support header version
    static const char* ERROR_TEXT_AVS_USP           = "error.text.avs.usp";     // un-support algorithm version
    static const char* ERROR_TEXT_KVS_USP           = "error.text.kvs.usp";     // un-support key version
    static const char* ERROR_TEXT_LEN_INC           = "error.text.len.inc";     // text length is wrong
    static const char* ERROR_AVS_USP                = "error.avs.usp";          // un-support algorithm version
    static const char* ERROR_KVS_USP                = "error.kvs.usp";          // un-support key version
    static const char* ERROR_KLV_USP                = "error.klv.usp";          // un-support key version
    static const char* ERROR_CFG_BUFMLT_OOR         = "error.cfg.bufmlt.oor";   // buffer multiple from config oor = OUT OF RANGE
    static const char* ERROR_FORMAT_EXPR            = "error.format.expr";      // format exper is incorrect, un-like ${index,type,options}
    static const char* ERROR_FORMATTER_UNKNOWN      = "error.formatter.ukn";    // formatter not found

    static const char* WARN_LANG_FILE_NOT_FOUND     = "warn.lang.file.nfd";
    static const char* WARN_LANG_FILE_READ          = "warn.lang.file.read";

    static const char* TIP_ERROR                    = "tip.error";
    static const char* TIP_ITEM_ERROR               = "tip.item.error";
    static const char* TIP_CMD_UNKNOWN              = "tip.cmd.unknown";
    static const char* TIP_OPS_UNKNOWN              = "tip.ops.unknown";
    static const char* TIP_LINE_MAIN                = "tip-line.main";
    static const char* TIP_LINE_TEXT                = "tip-line.text";
    static const char* TIP_LINE_FILE                = "tip-line.file";
    static const char* TIP_LINE_SHOW_NAME           = "tip-line.show.name";
    static const char* TIP_LINE_SHOW_VALUE          = "tip-line.show.value";
    static const char* TIP_LINE_HELP_NAME           = "tip-line.help.name";
    static const char* TIP_LINE_HELP_VALUE          = "tip-line.help.value";
    static const char* TIP_LINE_VD_WARNING          = "tip-line.vd.warning";
    static const char* TIP_LINE_VD_WARNING_IMP      = "tip-line.vd.warning.imp";

    static const char* HELP_OPS_M                   = "help.ops.-m";
    static const char* HELP_OPS_L                   = "help.ops.-l";
    static const char* HELP_OPS_S                   = "help.ops.-s";
    static const char* HELP_OPS_I                   = "help.ops.-i";
    static const char* HELP_OPS_O                   = "help.ops.-o";
    static const char* HELP_OPS_K                   = "help.ops.-k";
    static const char* HELP_OPS_F                   = "help.ops.-f";
    static const char* HELP_OPS_KF                  = "help.ops.-kf";
    static const char* HELP_OPS_KFL                 = "help.ops.-kfl";
    static const char* HELP_OPS_OPS                 = "help.ops.-op";
    static const char* HELP_OPS_WP                  = "help.ops.-wp";

    static const char* HELP_DRT_TEXT                = "help.ops.text";
    static const char* HELP_DRT_FILE                = "help.ops.file";
    static const char* HELP_DRT_HELP                = "help.ops.help";
    static const char* HELP_DRT_SHOW                = "help.ops.show";
    static const char* HELP_DRT_EXEC                = "help.ops.exec";
    static const char* HELP_DRT_EXIT                = "help.ops.exit";
    static const char* HELP_DRT_VALIDATE            = "help.ops.vd";
    static const char* HELP_DRT_ENCIP               = "help.ops.enc";
    static const char* HELP_DRT_DECIP               = "help.ops.dec";

    static const char* VDR_TITLE_ERROR              = "validate.title.error";
    static const char* VDR_TITLE_WARNING            = "validate.title.warning";
    static const char* VDR_TITLE_WARNING_IMP        = "validate.title.warning.imp";
    static const char* VDR_GOOD                     = "validate.good";
    static const char* VDR_MODE_UNKNOWN             = "validate.mode.unknown";
    static const char* VDR_TIN_MISS                 = "validate.ti.miss";
    static const char* VDR_FI_MISS                  = "validate.fi.miss";
    static const char* VDR_FO_MISS                  = "validate.fo.miss";
    static const char* VDR_FIO_EQUAL                = "validate.fio.equal";
    static const char* VDR_LEVEL_NAN                = "validate.lv.nan";
    static const char* VDR_LEVEL_OOR                = "validate.lv.oor";
    static const char* VDR_KF_INC                   = "validate.kf.wf";
    static const char* VDR_K_MISS                   = "validate.k.miss";
    static const char* VDR_K_SHORT                  = "validate.k.short";
    static const char* VDR_KFL_NFD                  = "validate.kfl.nfd";
    static const char* VDR_KFL_SHORT                = "validate.kfl.short";
    static const char* VDR_KFL_INC                  = "validate.kfl.inc";
    static const char* VDR_N_NAN                    = "validate.s.nan";
    static const char* VDR_N_INC                    = "validate.s.inc";
    static const char* VDR_N_OOR                    = "validate.s.oor";
    static const char* VDR_OPS_DD                   = "validate.ops.dd";
    static const char* VDR_OPS_DP                   = "validate.ops.dp";
    static const char* VDR_OPS_DOS                  = "validate.ops.dos";
    static const char* VDR_FST_TOOB                 = "validate.fst.toob";
    static const char* VDR_FST_TOOS                 = "validate.fst.toos";
    static const char* VDR_FL_NFD                   = "validate.fl.nfd";
    static const char* VDR_REG_INC                  = "validate.reg.inc";

    static const char* CIPHER_SCHEDULER_BEGIN       = "CI.scheduler.begin";
    static const char* CIPHER_SCHEDULER_END         = "CI.scheduler.end";
    static const char* CIPHER_TEXT_BEGIN            = "CI.text.begin";
    static const char* CIPHER_TEXT_END              = "CI.text.end";
    static const char* CIPHER_FILE_BEGIN            = "CI.file.begin";
    static const char* CIPHER_FILE_END              = "CI.file.end";
    static const char* CIPHER_DEL_BEGIN             = "CI.del.begin";
    static const char* CIPHER_DEL_END               = "CI.del.end";
    static const char* CIPHER_ITEM_ERROR            = "CI.item.error";
    static const char* CIPHER_ITEM_COMPETED         = "CI.item.completed";
    //@formatter:off
}
#endif //DIFFUSION_LANG_H
