// MESSAGE FM_BATTERY_STATUS support class

#pragma once

namespace mavlink {
namespace fmavlink {
namespace msg {

/**
 * @brief FM_BATTERY_STATUS message
 *
 * 轻量电池状态消息
 */
struct FM_BATTERY_STATUS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 20000;
    static constexpr size_t LENGTH = 9;
    static constexpr size_t MIN_LENGTH = 9;
    static constexpr uint8_t CRC_EXTRA = 13;
    static constexpr auto NAME = "FM_BATTERY_STATUS";


    uint32_t time_boot_ms; /*< [ms] 系统启动后的时间戳 */
    uint8_t battery_id; /*<  电池编号 */
    uint16_t voltage_mv; /*< [mV] 当前电压 */
    uint8_t remaining_pct; /*< [%] 剩余电量百分比 */
    uint8_t flags; /*<  电池状态标志位 */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  time_boot_ms: " << time_boot_ms << std::endl;
        ss << "  battery_id: " << +battery_id << std::endl;
        ss << "  voltage_mv: " << voltage_mv << std::endl;
        ss << "  remaining_pct: " << +remaining_pct << std::endl;
        ss << "  flags: " << +flags << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << time_boot_ms;                  // offset: 0
        map << voltage_mv;                    // offset: 4
        map << battery_id;                    // offset: 6
        map << remaining_pct;                 // offset: 7
        map << flags;                         // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> voltage_mv;                    // offset: 4
        map >> battery_id;                    // offset: 6
        map >> remaining_pct;                 // offset: 7
        map >> flags;                         // offset: 8
    }
};

} // namespace msg
} // namespace fmavlink
} // namespace mavlink
