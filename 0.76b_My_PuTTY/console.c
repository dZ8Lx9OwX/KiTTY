/*
 * Common pieces between the platform console frontend modules.
 */

#include <stdbool.h>
#include <stdarg.h>

#include "putty.h"
#include "misc.h"
#include "console.h"

const char hk_absentmsg_common_fmt[] =
    "服务器的主机密钥未缓存. 无法为\n"
    "您保证服务器就是您认为的计算机.\n"
    "服务器 %s 的密钥指纹是：\n"
    "%s\n";
const char hk_absentmsg_interactive_intro[] =
    "如果您信任此主机, 请输入\"y\"将\n"
    "密钥添加到PuTTY的缓存并继续连接.\n"
    "如果您只想进行一次连接, 在不将密\n"
    "钥添加到缓存的情况下, 请输入\"n\".\n"
    "如果您不信任此主机, 请按Return返回键\n"
    "放弃连接.\n";
const char hk_absentmsg_interactive_prompt[] =
    "是否将密钥存储在缓存中？ (y/n, Return返回键取消连接, "
    "i 了解更多信息) ";

const char hk_wrongmsg_common_fmt[] =
    "警告-潜在的安全漏洞！！！\n"
    "服务器的主机密钥与PuTTY缓存的主机\n"
    "密钥不匹配. 这意味着服务器管理员\n"
    "已更改了主机密钥, 或者您实际上已\n"
    "连接到另外一台计算机伪装的服务器.\n"
    "新的 %s 密钥指纹是：\n"
    "%s\n";
const char hk_wrongmsg_interactive_intro[] =
    "如果您想要接受此更改并且信任新的密钥,\n"
    "请输入\"y\"以更新密钥缓存并继续连接.\n"
    "如果您想继续连接但不更新\n"
    "密钥缓存,请输入\"n\".\n"
    "如果要完全放弃连接, 请按\n"
    "Return返回键以取消连接. \n"
    "按Return返回键是唯一保证安全的选择.\n";
const char hk_wrongmsg_interactive_prompt[] =
    "是否更新缓存密钥？(y/n, Return返回键取消连接, "
    "i 了解更多信息) ";

const char weakcrypto_msg_common_fmt[] =
    "服务器支持的第一个 %s 是 \n"
    "%s, 低于配置的警告阈值.\n";

const char weakhk_msg_common_fmt[] =
    "我们为此服务器存储的第一个主机密钥类型\n"
    "是 %s, 低于配置的警告阈值.\n"
    "服务器还提供以下类型的主机密钥\n"
    "高于警告阈值, 但我们尚未存储：\n"
    "%s\n";

const char console_continue_prompt[] = "是否继续连接? (y/n) ";
const char console_abandoned_msg[] = "已放弃连接.\n";

bool console_batch_mode = false;

/*
 * Error message and/or fatal exit functions, all based on
 * console_print_error_msg which the platform front end provides.
 */
void console_print_error_msg_fmt_v(
    const char *prefix, const char *fmt, va_list ap)
{
    char *msg = dupvprintf(fmt, ap);
    console_print_error_msg(prefix, msg);
    sfree(msg);
}

void console_print_error_msg_fmt(const char *prefix, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    console_print_error_msg_fmt_v(prefix, fmt, ap);
    va_end(ap);
}

void modalfatalbox(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    console_print_error_msg_fmt_v("致命错误！！", fmt, ap);
    va_end(ap);
    cleanup_exit(1);
}

void nonfatal(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    console_print_error_msg_fmt_v("错误！", fmt, ap);
    va_end(ap);
}

void console_connection_fatal(Seat *seat, const char *msg)
{
    console_print_error_msg("致命错误！！", msg);
    cleanup_exit(1);
}

/*
 * Console front ends redo their select() or equivalent every time, so
 * they don't need separate timer handling.
 */
void timer_change_notify(unsigned long next)
{
}
