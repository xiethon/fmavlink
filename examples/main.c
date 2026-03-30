#include <fmavlink/mavlink.h>

int main(void) {
    mavlink_message_t message;
    mavlink_msg_fm_battery_status_pack(
        1,
        1,
        &message,
        1000,
        0,
        24000,
        85,
        FM_BATTERY_FLAG_LOW
    );
    return message.msgid == MAVLINK_MSG_ID_FM_BATTERY_STATUS ? 0 : 1;
}
