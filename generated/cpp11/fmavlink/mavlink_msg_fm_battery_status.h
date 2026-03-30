#pragma once
// MESSAGE FM_BATTERY_STATUS PACKING

#define MAVLINK_MSG_ID_FM_BATTERY_STATUS 20000


typedef struct __mavlink_fm_battery_status_t {
 uint32_t time_boot_ms; /*< [ms] 系统启动后的时间戳*/
 uint16_t voltage_mv; /*< [mV] 当前电压*/
 uint8_t battery_id; /*<  电池编号*/
 uint8_t remaining_pct; /*< [%] 剩余电量百分比*/
 uint8_t flags; /*<  电池状态标志位*/
} mavlink_fm_battery_status_t;

#define MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN 9
#define MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN 9
#define MAVLINK_MSG_ID_20000_LEN 9
#define MAVLINK_MSG_ID_20000_MIN_LEN 9

#define MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC 13
#define MAVLINK_MSG_ID_20000_CRC 13



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FM_BATTERY_STATUS { \
    20000, \
    "FM_BATTERY_STATUS", \
    5, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_fm_battery_status_t, time_boot_ms) }, \
         { "battery_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_fm_battery_status_t, battery_id) }, \
         { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_fm_battery_status_t, voltage_mv) }, \
         { "remaining_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_fm_battery_status_t, remaining_pct) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_fm_battery_status_t, flags) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FM_BATTERY_STATUS { \
    "FM_BATTERY_STATUS", \
    5, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_fm_battery_status_t, time_boot_ms) }, \
         { "battery_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_fm_battery_status_t, battery_id) }, \
         { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_fm_battery_status_t, voltage_mv) }, \
         { "remaining_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_fm_battery_status_t, remaining_pct) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_fm_battery_status_t, flags) }, \
         } \
}
#endif

/**
 * @brief Pack a fm_battery_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] 系统启动后的时间戳
 * @param battery_id  电池编号
 * @param voltage_mv [mV] 当前电压
 * @param remaining_pct [%] 剩余电量百分比
 * @param flags  电池状态标志位
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fm_battery_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, uint8_t battery_id, uint16_t voltage_mv, uint8_t remaining_pct, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_uint16_t(buf, 4, voltage_mv);
    _mav_put_uint8_t(buf, 6, battery_id);
    _mav_put_uint8_t(buf, 7, remaining_pct);
    _mav_put_uint8_t(buf, 8, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#else
    mavlink_fm_battery_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.voltage_mv = voltage_mv;
    packet.battery_id = battery_id;
    packet.remaining_pct = remaining_pct;
    packet.flags = flags;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FM_BATTERY_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
}

/**
 * @brief Pack a fm_battery_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] 系统启动后的时间戳
 * @param battery_id  电池编号
 * @param voltage_mv [mV] 当前电压
 * @param remaining_pct [%] 剩余电量百分比
 * @param flags  电池状态标志位
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fm_battery_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t time_boot_ms, uint8_t battery_id, uint16_t voltage_mv, uint8_t remaining_pct, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_uint16_t(buf, 4, voltage_mv);
    _mav_put_uint8_t(buf, 6, battery_id);
    _mav_put_uint8_t(buf, 7, remaining_pct);
    _mav_put_uint8_t(buf, 8, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#else
    mavlink_fm_battery_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.voltage_mv = voltage_mv;
    packet.battery_id = battery_id;
    packet.remaining_pct = remaining_pct;
    packet.flags = flags;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FM_BATTERY_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#endif
}

/**
 * @brief Pack a fm_battery_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] 系统启动后的时间戳
 * @param battery_id  电池编号
 * @param voltage_mv [mV] 当前电压
 * @param remaining_pct [%] 剩余电量百分比
 * @param flags  电池状态标志位
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fm_battery_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,uint8_t battery_id,uint16_t voltage_mv,uint8_t remaining_pct,uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_uint16_t(buf, 4, voltage_mv);
    _mav_put_uint8_t(buf, 6, battery_id);
    _mav_put_uint8_t(buf, 7, remaining_pct);
    _mav_put_uint8_t(buf, 8, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#else
    mavlink_fm_battery_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.voltage_mv = voltage_mv;
    packet.battery_id = battery_id;
    packet.remaining_pct = remaining_pct;
    packet.flags = flags;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FM_BATTERY_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
}

/**
 * @brief Encode a fm_battery_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fm_battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fm_battery_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fm_battery_status_t* fm_battery_status)
{
    return mavlink_msg_fm_battery_status_pack(system_id, component_id, msg, fm_battery_status->time_boot_ms, fm_battery_status->battery_id, fm_battery_status->voltage_mv, fm_battery_status->remaining_pct, fm_battery_status->flags);
}

/**
 * @brief Encode a fm_battery_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fm_battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fm_battery_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fm_battery_status_t* fm_battery_status)
{
    return mavlink_msg_fm_battery_status_pack_chan(system_id, component_id, chan, msg, fm_battery_status->time_boot_ms, fm_battery_status->battery_id, fm_battery_status->voltage_mv, fm_battery_status->remaining_pct, fm_battery_status->flags);
}

/**
 * @brief Encode a fm_battery_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fm_battery_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fm_battery_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fm_battery_status_t* fm_battery_status)
{
    return mavlink_msg_fm_battery_status_pack_status(system_id, component_id, _status, msg,  fm_battery_status->time_boot_ms, fm_battery_status->battery_id, fm_battery_status->voltage_mv, fm_battery_status->remaining_pct, fm_battery_status->flags);
}

/**
 * @brief Send a fm_battery_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] 系统启动后的时间戳
 * @param battery_id  电池编号
 * @param voltage_mv [mV] 当前电压
 * @param remaining_pct [%] 剩余电量百分比
 * @param flags  电池状态标志位
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fm_battery_status_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint8_t battery_id, uint16_t voltage_mv, uint8_t remaining_pct, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_uint16_t(buf, 4, voltage_mv);
    _mav_put_uint8_t(buf, 6, battery_id);
    _mav_put_uint8_t(buf, 7, remaining_pct);
    _mav_put_uint8_t(buf, 8, flags);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS, buf, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#else
    mavlink_fm_battery_status_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.voltage_mv = voltage_mv;
    packet.battery_id = battery_id;
    packet.remaining_pct = remaining_pct;
    packet.flags = flags;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS, (const char *)&packet, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#endif
}

/**
 * @brief Send a fm_battery_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fm_battery_status_send_struct(mavlink_channel_t chan, const mavlink_fm_battery_status_t* fm_battery_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fm_battery_status_send(chan, fm_battery_status->time_boot_ms, fm_battery_status->battery_id, fm_battery_status->voltage_mv, fm_battery_status->remaining_pct, fm_battery_status->flags);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS, (const char *)fm_battery_status, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fm_battery_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint8_t battery_id, uint16_t voltage_mv, uint8_t remaining_pct, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_uint16_t(buf, 4, voltage_mv);
    _mav_put_uint8_t(buf, 6, battery_id);
    _mav_put_uint8_t(buf, 7, remaining_pct);
    _mav_put_uint8_t(buf, 8, flags);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS, buf, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#else
    mavlink_fm_battery_status_t *packet = (mavlink_fm_battery_status_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->voltage_mv = voltage_mv;
    packet->battery_id = battery_id;
    packet->remaining_pct = remaining_pct;
    packet->flags = flags;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FM_BATTERY_STATUS, (const char *)packet, MAVLINK_MSG_ID_FM_BATTERY_STATUS_MIN_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN, MAVLINK_MSG_ID_FM_BATTERY_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE FM_BATTERY_STATUS UNPACKING


/**
 * @brief Get field time_boot_ms from fm_battery_status message
 *
 * @return [ms] 系统启动后的时间戳
 */
static inline uint32_t mavlink_msg_fm_battery_status_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field battery_id from fm_battery_status message
 *
 * @return  电池编号
 */
static inline uint8_t mavlink_msg_fm_battery_status_get_battery_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field voltage_mv from fm_battery_status message
 *
 * @return [mV] 当前电压
 */
static inline uint16_t mavlink_msg_fm_battery_status_get_voltage_mv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field remaining_pct from fm_battery_status message
 *
 * @return [%] 剩余电量百分比
 */
static inline uint8_t mavlink_msg_fm_battery_status_get_remaining_pct(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field flags from fm_battery_status message
 *
 * @return  电池状态标志位
 */
static inline uint8_t mavlink_msg_fm_battery_status_get_flags(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a fm_battery_status message into a struct
 *
 * @param msg The message to decode
 * @param fm_battery_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_fm_battery_status_decode(const mavlink_message_t* msg, mavlink_fm_battery_status_t* fm_battery_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fm_battery_status->time_boot_ms = mavlink_msg_fm_battery_status_get_time_boot_ms(msg);
    fm_battery_status->voltage_mv = mavlink_msg_fm_battery_status_get_voltage_mv(msg);
    fm_battery_status->battery_id = mavlink_msg_fm_battery_status_get_battery_id(msg);
    fm_battery_status->remaining_pct = mavlink_msg_fm_battery_status_get_remaining_pct(msg);
    fm_battery_status->flags = mavlink_msg_fm_battery_status_get_flags(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN? msg->len : MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN;
        memset(fm_battery_status, 0, MAVLINK_MSG_ID_FM_BATTERY_STATUS_LEN);
    memcpy(fm_battery_status, _MAV_PAYLOAD(msg), len);
#endif
}
