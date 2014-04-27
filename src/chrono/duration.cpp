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
#include <peelo/chrono/duration.hpp>

namespace peelo
{
    const int duration::hours_per_day = 24;
    const int duration::minutes_per_day = 1440;
    const int duration::minutes_per_hour = 60;
    const int duration::seconds_per_day = 86400;
    const int duration::seconds_per_hour = 3600;
    const int duration::seconds_per_minute = 60;

    duration::duration(int days, int hours, int minutes, int seconds)
        : m_seconds(
                days * seconds_per_day
                + hours * seconds_per_hour
                + minutes * seconds_per_minute
                + seconds
        ) {}
    
    duration::duration(const duration& that)
        : m_seconds(that.m_seconds) {}

    duration& duration::assign(const duration& that)
    {
        m_seconds = that.m_seconds;

        return *this;
    }

    bool duration::equals(const duration& that) const
    {
        return m_seconds == that.m_seconds;
    }

    int duration::compare(const duration& that) const
    {
        return m_seconds > that.m_seconds ? 1 : m_seconds < that.m_seconds ? -1 : 0;
    }

    duration duration::operator+(const duration& that) const
    {
        return duration(0, 0, 0, m_seconds + that.m_seconds);
    }

    duration duration::operator-(const duration& that) const
    {
        return duration(0, 0, 0, m_seconds - that.m_seconds);
    }

    duration duration::operator*(int factor) const
    {
        return duration(0, 0, 0, m_seconds * factor);
    }

    duration duration::operator/(int quotient) const
    {
        return duration(0, 0, 0, m_seconds / quotient);
    }
}
