/*
 * Copyright (c) 2014, peelo.net
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <peelo/chrono/datetime.hpp>

namespace peelo
{
    datetime::datetime(int year,
                       month_e month,
                       int day,
                       int hour,
                       int minute,
                       int second)
        : m_date(year, month, day)
        , m_time(hour, minute, second) {}

    datetime::datetime(const class date& date, const class time& time)
        : m_date(date)
        , m_time(time) {}

    datetime::datetime(const datetime& that)
        : m_date(that.m_date)
        , m_time(that.m_time) {}

    datetime datetime::now()
    {
        return datetime(date::today(), time::now());
    }

    datetime& datetime::assign(const datetime& that)
    {
        m_date.assign(that.m_date);
        m_time.assign(that.m_time);

        return *this;
    }

    datetime& datetime::assign(const class date& date, const class time& time)
    {
        m_date.assign(date);
        m_time.assign(time);

        return *this;
    }

    bool datetime::equals(const datetime& that) const
    {
        return m_date.equals(that.m_date) && m_time.equals(that.m_time);
    }

    int datetime::compare(const datetime& that) const
    {
        int cmp = m_date.compare(that.m_date);

        if (cmp != 0)
        {
            return cmp;
        } else {
            return m_time.compare(that.m_time);
        }
    }
}
