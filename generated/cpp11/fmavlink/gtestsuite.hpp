/** @file
 *	@brief MAVLink comm testsuite protocol generated from fmavlink.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "fmavlink.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(fmavlink, FM_BATTERY_STATUS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::fmavlink::msg::FM_BATTERY_STATUS packet_in{};
    packet_in.time_boot_ms = 963497464;
    packet_in.battery_id = 151;
    packet_in.voltage_mv = 17443;
    packet_in.remaining_pct = 218;
    packet_in.flags = 29;

    mavlink::fmavlink::msg::FM_BATTERY_STATUS packet1{};
    mavlink::fmavlink::msg::FM_BATTERY_STATUS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.time_boot_ms, packet2.time_boot_ms);
    EXPECT_EQ(packet1.battery_id, packet2.battery_id);
    EXPECT_EQ(packet1.voltage_mv, packet2.voltage_mv);
    EXPECT_EQ(packet1.remaining_pct, packet2.remaining_pct);
    EXPECT_EQ(packet1.flags, packet2.flags);
}

#ifdef TEST_INTEROP
TEST(fmavlink_interop, FM_BATTERY_STATUS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_fm_battery_status_t packet_c {
         963497464, 17443, 151, 218, 29
    };

    mavlink::fmavlink::msg::FM_BATTERY_STATUS packet_in{};
    packet_in.time_boot_ms = 963497464;
    packet_in.battery_id = 151;
    packet_in.voltage_mv = 17443;
    packet_in.remaining_pct = 218;
    packet_in.flags = 29;

    mavlink::fmavlink::msg::FM_BATTERY_STATUS packet2{};

    mavlink_msg_fm_battery_status_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.time_boot_ms, packet2.time_boot_ms);
    EXPECT_EQ(packet_in.battery_id, packet2.battery_id);
    EXPECT_EQ(packet_in.voltage_mv, packet2.voltage_mv);
    EXPECT_EQ(packet_in.remaining_pct, packet2.remaining_pct);
    EXPECT_EQ(packet_in.flags, packet2.flags);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
