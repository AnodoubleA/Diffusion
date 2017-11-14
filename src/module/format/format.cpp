//
// Created by Alice on 2017.03.18.
//

#include "content.h"
#include "levels.h"
#include "content_handler.h"
#include "format.h"

namespace lc{
    namespace mf{
        const char* OPEN = "${";
        const char* CLOSE = "}";
        MultiArgHandler handler = MultiArgHandler();
        Format format;
        std::map<std::string, Formatter*> map_f;
        std::regex* reg_number = new std::regex("^[0-9]+$", std::regex_constants::extended);
        std::match_results<std::string::const_iterator> result;
        std::string DEF_FORMATTER = "%";

        //@formatter:off
        uint64 MILLISECOND     = 1;
        uint64 SECOND         = MILLISECOND * 1000;
        uint64 MINUTE         = SECOND * 60;
        uint64 HOUR           = MINUTE * 60;
        uint64 DAY            = HOUR * 24;
        uint64 MONTH          = DAY * 30;
        uint64 YEAR           = (uint64)(DAY * 365 + 5 * HOUR + 48 * MINUTE + 45.9747 * SECOND);
        uint64 CENTURY        = YEAR * 100;

        uint64 BT             = 1;
        uint64 KB             = BT * 1024;
        uint64 MB             = KB * 1024;
        uint64 GB             = MB * 1024;
        uint64 TB             = GB * 1024;
        uint64 PB             = TB * 1024;
        uint64 ZB             = TB * 1024;
        uint64 EB             = ZB * 1024;
        //@formatter:on
    }

    void init_formatter() {
        mf::map_f["%"] = new CFormatter();
        mf::map_f["+"] = new SelfFormatter();
        LinkLevel* linkTime = new LinkLevel(mf::MILLISECOND, "SSS");
        linkTime->link(mf::SECOND, "ss")
                ->link(mf::MINUTE, "mm")
                ->link(mf::HOUR, "HH")
                ->link(mf::DAY, "dd")
                ->link(mf::MONTH, "MM")
                ->link(mf::YEAR, "yyyy")
                ->link(mf::CENTURY, "CN");

        mf::map_f["t+"] = new LevelFormatter(linkTime);

        SimpleLevel* simpleTime = new SimpleLevel(mf::MILLISECOND, "SSS", "毫秒");
        simpleTime->link(mf::SECOND, "ss", "秒")
                ->link(mf::MINUTE, "mm", "分")
                ->link(mf::HOUR, "HH", "时")
                ->link(mf::DAY, "dd", "日")
                ->link(mf::MONTH, "MM", "月")
                ->link(mf::YEAR, "yyyy", "年")
                ->link(mf::CENTURY, "CN", "世纪");
        mf::map_f["t"] = new LevelFormatter(simpleTime);

        SimpleLevel* simpleSize = new SimpleLevel(mf::KB, "KB", "KB");
        simpleSize->link(mf::MB, "MB", "MB")
                ->link(mf::GB, "GB", "GB")
                ->link(mf::TB, "TB", "TB")
                ->link(mf::PB, "PB", "PB")
                ->link(mf::ZB, "ZB", "ZB")
                ->link(mf::EB, "EB", "EB");
        mf::map_f["d"] = new LevelFormatter(simpleSize);
    }
}

