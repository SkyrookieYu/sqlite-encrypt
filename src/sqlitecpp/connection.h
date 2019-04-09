﻿
#ifndef ___HEADFILE_A7E2D32B_B83E_44AB_A6C6_98E03E0EDDBD_
#define ___HEADFILE_A7E2D32B_B83E_44AB_A6C6_98E03E0EDDBD_

#include <vector>

#define SQLITE_HAS_CODEC 1
#include <sqlite3.h>

#include <nut/platform/platform.h>
#include <nut/rc/rc_ptr.h>

#include "param.h"
#include "statement.h"
#include "result_set.h"


namespace sqlitecpp
{

class Connection
{
    NUT_REF_COUNTABLE

public:
    Connection() = default;
    explicit Connection(sqlite3 *db);

    /**
     * @param db_file File path encoded in UTF-8
     */
    explicit Connection(const char *db_file);
    explicit Connection(const std::string& db_file);

    ~Connection();

    /**
     * @param db_file File path encoded in UTF-8
     */
    bool open(const char *db_file);
    bool open(const std::string& db_file);

    bool close();

#if defined(SQLITE_HAS_CODEC) && SQLITE_HAS_CODEC
    /**
     * 设置加密密码，或者用密码打开已加密数据库
     */
    bool set_key(const char *key, int key_len = -1);

    /**
     * 更改密数据库码
     */
    bool change_key(const char *key, int key_len = -1);
#endif

    sqlite3* get_raw_db() const;

    bool is_valid() const;

    bool is_auto_commit() const;
    void set_auto_commit(bool b);

    bool is_throw_exceptions() const;
    void set_throw_exceptions(bool b);

    int get_last_error_code() const;
    const std::string& get_last_error_msg() const;

    bool start();
    bool commit();
    bool rollback();

    /**
     * 压缩数据库文件
     */
    bool vacuum();

    bool execute_update(const char *sql);
    bool execute_update(
        const char *sql, const Param& arg1, const Param& arg2 = Param::nop(),
        const Param& arg3 = Param::nop(), const Param& arg4 = Param::nop(),
        const Param& arg5 = Param::nop(), const Param& arg6 = Param::nop(),
        const Param& arg7 = Param::nop(), const Param& arg8 = Param::nop(),
        const Param& arg9 = Param::nop());
    bool execute_update(const char *sql, const std::vector<Param>& args);

    nut::rc_ptr<ResultSet> execute_query(
        const char *sql, const Param& arg1 = Param::nop(),
        const Param& arg2 = Param::nop(), const Param& arg3 = Param::nop(),
        const Param& arg4 = Param::nop(), const Param& arg5 = Param::nop(),
        const Param& arg6 = Param::nop(), const Param& arg7 = Param::nop(),
        const Param& arg8 = Param::nop(), const Param& arg9 = Param::nop());
    nut::rc_ptr<ResultSet> execute_query(const char *sql, const std::vector<Param>& args);

private:
    void on_error(int err = SQLITE_OK, const char *msg = nullptr);

private:
    sqlite3 *_sqlite = nullptr;
    bool _auto_commit = true;
    bool _throw_exceptions = false;
    int _last_error = SQLITE_OK;
    std::string _last_error_msg;
};

}

#endif
