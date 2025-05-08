#ifndef CONFIG_KEYS_H
#define CONFIG_KEYS_H

#include <vector>
#include "config/ConfigKey.h"
#include "config/ConfigSuffix.h"
#include "config/KeyType.h"

namespace config {

// -- Protocol configuration suffixes --
inline const StringConfigSuffix PROTOCOL_ADDRESS        {".address",     {KeyType::CONFIG}};
inline const IntegerConfigSuffix PROTOCOL_PORT          {".port",        {KeyType::CONFIG}};
inline const StringConfigSuffix PROTOCOL_DEVICES        {".devices",     {KeyType::CONFIG}};
inline const LongConfigSuffix   PROTOCOL_INTERVAL       {".interval",    {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_SSL          {".ssl",         {KeyType::CONFIG}};
inline const IntegerConfigSuffix PROTOCOL_TIMEOUT       {".timeout",     {KeyType::CONFIG}};
inline const StringConfigKey    DEVICE_PASSWORD        {"devicePassword",          {KeyType::DEVICE}};
inline const StringConfigSuffix PROTOCOL_DEVICE_PASSWORD{".devicePassword",         {KeyType::CONFIG}};
inline const IntegerConfigSuffix PROTOCOL_MASK          {".mask",        {KeyType::CONFIG}};
inline const IntegerConfigSuffix PROTOCOL_MESSAGE_LENGTH{".messageLength",{KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_EXTENDED     {".extended",    {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_UTF8         {".utf8",        {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_CAN          {".can",         {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_ACK          {".ack",         {KeyType::CONFIG, KeyType::DEVICE}, false};
inline const BooleanConfigSuffix PROTOCOL_IGNORE_FIX_TIME{".ignoreFixTime", {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_DECODE_LOW   {".decodeLow",   {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_LONG_DATE    {".longDate",    {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_DECIMAL_FUEL {".decimalFuel", {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_CUSTOM       {".custom",      {KeyType::CONFIG}};
inline const StringConfigSuffix PROTOCOL_FORM          {".form",        {KeyType::CONFIG}};
inline const StringConfigSuffix PROTOCOL_CONFIG        {".config",      {KeyType::CONFIG}};
inline const StringConfigSuffix PROTOCOL_ALARM_MAP     {".alarmMap",    {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_PREFIX       {".prefix",      {KeyType::CONFIG}};
inline const StringConfigKey    PROTOCOL_TYPE          {"suntech.protocolType",   {KeyType::CONFIG, KeyType::DEVICE}};
inline const StringConfigKey    PROTOCOL_HBM           {"suntech.hbm",           {KeyType::CONFIG, KeyType::DEVICE}};
inline const BooleanConfigSuffix PROTOCOL_INCLUDE_ADC  {".includeAdc",  {KeyType::CONFIG, KeyType::DEVICE}};
inline const BooleanConfigSuffix PROTOCOL_INCLUDE_RPM  {".includeRpm",  {KeyType::CONFIG, KeyType::DEVICE}};
inline const BooleanConfigSuffix PROTOCOL_INCLUDE_TEMPERATURE{".includeTemp", {KeyType::CONFIG, KeyType::DEVICE}};
inline const BooleanConfigSuffix PROTOCOL_DISABLE_COMMANDS{".disableCommands", {KeyType::CONFIG}};
inline const StringConfigSuffix PROTOCOL_FORMAT        {".format",      {KeyType::CONFIG, KeyType::DEVICE}};
inline const StringConfigSuffix PROTOCOL_DATE_FORMAT   {".dateFormat",  {KeyType::DEVICE}};
inline const StringConfigKey    DECODER_TIMEZONE       {"decoder.timezone",      {KeyType::CONFIG, KeyType::DEVICE}};
inline const StringConfigKey    ORBCOMM_ACCESS_ID      {"orbcomm.accessId",      {KeyType::CONFIG}};
inline const StringConfigKey    ORBCOMM_PASSWORD       {"orbcomm.password",      {KeyType::CONFIG}};
inline const BooleanConfigSuffix PROTOCOL_ALTERNATIVE  {".alternative", {KeyType::CONFIG, KeyType::DEVICE}, false};
inline const BooleanConfigSuffix PROTOCOL_LANGUAGE     {".language",    {KeyType::CONFIG, KeyType::DEVICE}, false};

// -- Server configuration keys --
inline const LongConfigKey      SERVER_BUFFERING_THRESHOLD{"server.buffering.threshold", {KeyType::CONFIG}};
inline const IntegerConfigKey   SERVER_TIMEOUT          {"server.timeout",            {KeyType::CONFIG}};
inline const BooleanConfigKey   SERVER_INSTANT_ACKNOWLEDGEMENT{"server.instantAcknowledgement", {KeyType::CONFIG}};
inline const StringConfigKey    SERVER_STATISTICS        {"server.statistics",        {KeyType::CONFIG}, "https://www.traccar.org/analytics/"};

// -- Event configuration keys --
inline const DoubleConfigKey    EVENT_FUEL_DROP_THRESHOLD {"fuelDropThreshold",        {KeyType::SERVER, KeyType::DEVICE}, 0.0};
inline const DoubleConfigKey    EVENT_FUEL_INCREASE_THRESHOLD{"fuelIncreaseThreshold",  {KeyType::SERVER, KeyType::DEVICE}, 0.0};
inline const DoubleConfigKey    EVENT_OVERSPEED_LIMIT     {"speedLimit",              {KeyType::SERVER, KeyType::DEVICE}, 0.0};
inline const BooleanConfigKey   DEVICE_SHARE_DISABLE      {"disableShare",            {KeyType::SERVER}};
inline const DoubleConfigKey    EVENT_OVERSPEED_THRESHOLD_MULTIPLIER{"event.overspeed.thresholdMultiplier", {KeyType::CONFIG}, 1.0};
inline const LongConfigKey      EVENT_OVERSPEED_MINIMAL_DURATION{"event.overspeed.minimalDuration", {KeyType::CONFIG}};
inline const BooleanConfigKey   EVENT_OVERSPEED_PREFER_LOWEST{"event.overspeed.preferLowest", {KeyType::CONFIG}};
inline const DoubleConfigKey    EVENT_BEHAVIOR_ACCELERATION_THRESHOLD{"event.behavior.accelerationThreshold", {KeyType::CONFIG}};
inline const DoubleConfigKey    EVENT_BEHAVIOR_BRAKING_THRESHOLD{"event.behavior.brakingThreshold", {KeyType::CONFIG}};
inline const BooleanConfigKey   EVENT_IGNORE_DUPLICATE_ALERTS{"event.ignoreDuplicateAlerts", {KeyType::CONFIG}, true};
inline const BooleanConfigKey   EVENT_MOTION_PROCESS_INVALID_POSITIONS{"event.motion.processInvalidPositions", {KeyType::CONFIG, KeyType::DEVICE}, false};
inline const DoubleConfigKey    EVENT_MOTION_SPEED_THRESHOLD{"event.motion.speedThreshold", {KeyType::CONFIG, KeyType::DEVICE}, 0.01};

// -- Geofence keys --
inline const DoubleConfigKey    GEOFENCE_POLYLINE_DISTANCE{"geofence.polylineDistance", {KeyType::CONFIG}, 25.0};

// -- Database keys --
inline const BooleanConfigKey   DATABASE_MEMORY          {"database.memory",         {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_DRIVER_FILE     {"database.driverFile",     {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_DRIVER          {"database.driver",         {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_URL             {"database.url",            {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_USER            {"database.user",           {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_PASSWORD        {"database.password",       {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_CHANGELOG       {"database.changelog",      {KeyType::CONFIG}, "./schema/changelog-master.xml"};
inline const IntegerConfigKey   DATABASE_MAX_POOL_SIZE   {"database.maxPoolSize",    {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_CHECK_CONNECTION{"database.checkConnection",{KeyType::CONFIG}, "SELECT 1"};
inline const BooleanConfigKey   DATABASE_SAVE_ORIGINAL   {"database.saveOriginal",   {KeyType::CONFIG}};
inline const BooleanConfigKey   DATABASE_THROTTLE_UNKNOWN{"database.throttleUnknown", {KeyType::CONFIG}};
inline const BooleanConfigKey   DATABASE_REGISTER_UNKNOWN{"database.registerUnknown", {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_REGISTER_UNKNOWN_DEFAULT_CATEGORY{"database.registerUnknown.defaultCategory", {KeyType::CONFIG}};
inline const LongConfigKey      DATABASE_REGISTER_UNKNOWN_DEFAULT_GROUP_ID{"database.registerUnknown.defaultGroupId", {KeyType::CONFIG}};
inline const StringConfigKey    DATABASE_REGISTER_UNKNOWN_REGEX{"database.registerUnknown.regex", {KeyType::CONFIG}, "\\w{3,15}"};
inline const BooleanConfigKey   DATABASE_SAVE_EMPTY       {"database.saveEmpty",      {KeyType::CONFIG}};

// -- User keys --
inline const IntegerConfigKey   USERS_DEFAULT_DEVICE_LIMIT{"users.defaultDeviceLimit", {KeyType::CONFIG}, -1};
inline const IntegerConfigKey   USERS_DEFAULT_EXPIRATION_DAYS{"users.defaultExpirationDays", {KeyType::CONFIG}};

// -- LDAP keys --
inline const StringConfigKey    LDAP_URL                  {"ldap.url",                 {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_USER                 {"ldap.user",                {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_PASSWORD             {"ldap.password",            {KeyType::CONFIG}};
inline const BooleanConfigKey   LDAP_FORCE                {"ldap.force",               {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_BASE                 {"ldap.base",                {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_ID_ATTRIBUTE         {"ldap.idAttribute",         {KeyType::CONFIG}, "uid"};
inline const StringConfigKey    LDAP_NAME_ATTRIBUTE       {"ldap.nameAttribute",       {KeyType::CONFIG}, "cn"};
inline const StringConfigKey    LDAP_MAIN_ATTRIBUTE       {"ldap.mailAttribute",       {KeyType::CONFIG}, "mail"};
inline const StringConfigKey    LDAP_SEARCH_FILTER        {"ldap.searchFilter",        {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_ADMIN_FILTER         {"ldap.adminFilter",         {KeyType::CONFIG}};
inline const StringConfigKey    LDAP_ADMIN_GROUP          {"ldap.adminGroup",          {KeyType::CONFIG}};

// -- OpenID Connect keys --
inline const BooleanConfigKey   OPENID_FORCE              {"openid.force",             {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_CLIENT_ID          {"openid.clientId",          {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_CLIENT_SECRET      {"openid.clientSecret",      {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_ISSUER_URL         {"openid.issuerUrl",         {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_AUTH_URL           {"openid.authUrl",           {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_TOKEN_URL          {"openid.tokenUrl",          {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_USERINFO_URL       {"openid.userInfoUrl",       {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_GROUPS_CLAIM_NAME  {"openid.groupsClaimName",   {KeyType::CONFIG}, "groups"};
inline const StringConfigKey    OPENID_ALLOW_GROUP         {"openid.allowGroup",        {KeyType::CONFIG}};
inline const StringConfigKey    OPENID_ADMIN_GROUP        {"openid.adminGroup",        {KeyType::CONFIG}};

// -- Status keys --
inline const LongConfigKey      STATUS_TIMEOUT            {"status.timeout",           {KeyType::CONFIG}, 600L};
inline const StringConfigKey    STATUS_IGNORE_OFFLINE     {"status.ignoreOffline",     {KeyType::CONFIG}};

// -- Media keys --
inline const StringConfigKey    MEDIA_PATH                {"media.path",               {KeyType::CONFIG}, "./media"};

// -- Web interface keys --
inline const StringConfigKey    WEB_ADDRESS               {"web.address",              {KeyType::CONFIG}};
inline const IntegerConfigKey   WEB_PORT                  {"web.port",                 {KeyType::CONFIG}, 8080};
inline const IntegerConfigKey   WEB_MAX_REQUESTS_PER_SECOND{"web.maxRequestsPerSec",   {KeyType::CONFIG}};
inline const IntegerConfigKey   WEB_MAX_REQUEST_SECONDS   {"web.maxRequestSec",        {KeyType::CONFIG}, 600};
inline const StringConfigKey    WEB_PATH                  {"web.path",                 {KeyType::CONFIG}, "./web"};
inline const StringConfigKey    WEB_OVERRIDE              {"web.override",             {KeyType::CONFIG}, "./override"};
inline const LongConfigKey      WEB_TIMEOUT               {"web.timeout",              {KeyType::CONFIG}, 300000L};
inline const IntegerConfigKey   WEB_SESSION_TIMEOUT       {"web.sessionTimeout",       {KeyType::CONFIG}};
inline const BooleanConfigKey   WEB_CONSOLE               {"web.console",              {KeyType::CONFIG}};
inline const BooleanConfigKey   WEB_DEBUG                 {"web.debug",                {KeyType::CONFIG}};
inline const StringConfigKey    WEB_SERVICE_ACCOUNT_TOKEN {"web.serviceAccountToken",  {KeyType::CONFIG}};
inline const StringConfigKey    WEB_ORIGIN                {"web.origin",               {KeyType::CONFIG}};
inline const StringConfigKey    WEB_CACHE_CONTROL         {"web.cacheControl",         {KeyType::CONFIG}, "max-age=3600,public"};

// -- Logger keys --
inline const BooleanConfigKey   LOGGER_CONSOLE            {"logger.console",           {KeyType::CONFIG}};
inline const BooleanConfigKey   LOGGER_QUERIES            {"logger.queries",           {KeyType::CONFIG}};
inline const StringConfigKey    LOGGER_FILE               {"logger.file",              {KeyType::CONFIG}, "./logs/tracker-server.log"};
inline const StringConfigKey    LOGGER_LEVEL              {"logger.level",             {KeyType::CONFIG}, "info"};
inline const BooleanConfigKey   LOGGER_FULL_STACK_TRACES  {"logger.fullStackTraces",   {KeyType::CONFIG}};
inline const BooleanConfigKey   LOGGER_ROTATE             {"logger.rotate",            {KeyType::CONFIG}, true};
inline const BooleanConfigKey   LOGGER_TEXT_PROTOCOL      {"logger.decodeTextData",    {KeyType::CONFIG}, true};
inline const StringConfigKey    LOGGER_ROTATE_INTERVAL    {"logger.rotate.interval",   {KeyType::CONFIG}, "day"};
inline const StringConfigKey    LOGGER_ATTRIBUTES         {"logger.attributes",        {KeyType::CONFIG}, "time,position,speed,course,accuracy,result"};

// -- Broadcast keys --
inline const StringConfigKey    BROADCAST_TYPE            {"broadcast.type",           {KeyType::CONFIG}};
inline const StringConfigKey    BROADCAST_INTERFACE       {"broadcast.interface",      {KeyType::CONFIG}};
inline const StringConfigKey    BROADCAST_ADDRESS         {"broadcast.address",        {KeyType::CONFIG}};
inline const IntegerConfigKey   BROADCAST_PORT            {"broadcast.port",           {KeyType::CONFIG}};
inline const BooleanConfigKey   BROADCAST_SECONDARY       {"broadcast.secondary",      {KeyType::CONFIG}};

} // namespace config

#endif // CONFIG_KEYS_H
