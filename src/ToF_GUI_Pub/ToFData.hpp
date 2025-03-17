// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file ToFData.hpp
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef FAST_DDS_GENERATED__TOFDATA_HPP
#define FAST_DDS_GENERATED__TOFDATA_HPP

#include <cstdint>
#include <utility>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(TOFDATA_SOURCE)
#define TOFDATA_DllAPI __declspec( dllexport )
#else
#define TOFDATA_DllAPI __declspec( dllimport )
#endif // TOFDATA_SOURCE
#else
#define TOFDATA_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define TOFDATA_DllAPI
#endif // _WIN32

/*!
 * @brief This class represents the structure ToFData defined by the user in the IDL file.
 * @ingroup ToFData
 */
class ToFData
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport ToFData()
    {
    }

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~ToFData()
    {
    }

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object ToFData that will be copied.
     */
    eProsima_user_DllExport ToFData(
            const ToFData& x)
    {
                    m_sec = x.m_sec;

                    m_distance = x.m_distance;

                    m_threshold = x.m_threshold;

                    m_intensity = x.m_intensity;

                    m_battery = x.m_battery;

                    m_enable = x.m_enable;

    }

    /*!
     * @brief Move constructor.
     * @param x Reference to the object ToFData that will be copied.
     */
    eProsima_user_DllExport ToFData(
            ToFData&& x) noexcept
    {
        m_sec = x.m_sec;
        m_distance = x.m_distance;
        m_threshold = x.m_threshold;
        m_intensity = x.m_intensity;
        m_battery = x.m_battery;
        m_enable = x.m_enable;
    }

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object ToFData that will be copied.
     */
    eProsima_user_DllExport ToFData& operator =(
            const ToFData& x)
    {

                    m_sec = x.m_sec;

                    m_distance = x.m_distance;

                    m_threshold = x.m_threshold;

                    m_intensity = x.m_intensity;

                    m_battery = x.m_battery;

                    m_enable = x.m_enable;

        return *this;
    }

    /*!
     * @brief Move assignment.
     * @param x Reference to the object ToFData that will be copied.
     */
    eProsima_user_DllExport ToFData& operator =(
            ToFData&& x) noexcept
    {

        m_sec = x.m_sec;
        m_distance = x.m_distance;
        m_threshold = x.m_threshold;
        m_intensity = x.m_intensity;
        m_battery = x.m_battery;
        m_enable = x.m_enable;
        return *this;
    }

    /*!
     * @brief Comparison operator.
     * @param x ToFData object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const ToFData& x) const
    {
        return (m_sec == x.m_sec &&
           m_distance == x.m_distance &&
           m_threshold == x.m_threshold &&
           m_intensity == x.m_intensity &&
           m_battery == x.m_battery &&
           m_enable == x.m_enable);
    }

    /*!
     * @brief Comparison operator.
     * @param x ToFData object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const ToFData& x) const
    {
        return !(*this == x);
    }

    /*!
     * @brief This function sets a value in member sec
     * @param _sec New value for member sec
     */
    eProsima_user_DllExport void sec(
            int32_t _sec)
    {
        m_sec = _sec;
    }

    /*!
     * @brief This function returns the value of member sec
     * @return Value of member sec
     */
    eProsima_user_DllExport int32_t sec() const
    {
        return m_sec;
    }

    /*!
     * @brief This function returns a reference to member sec
     * @return Reference to member sec
     */
    eProsima_user_DllExport int32_t& sec()
    {
        return m_sec;
    }


    /*!
     * @brief This function sets a value in member distance
     * @param _distance New value for member distance
     */
    eProsima_user_DllExport void distance(
            float _distance)
    {
        m_distance = _distance;
    }

    /*!
     * @brief This function returns the value of member distance
     * @return Value of member distance
     */
    eProsima_user_DllExport float distance() const
    {
        return m_distance;
    }

    /*!
     * @brief This function returns a reference to member distance
     * @return Reference to member distance
     */
    eProsima_user_DllExport float& distance()
    {
        return m_distance;
    }


    /*!
     * @brief This function sets a value in member threshold
     * @param _threshold New value for member threshold
     */
    eProsima_user_DllExport void threshold(
            int32_t _threshold)
    {
        m_threshold = _threshold;
    }

    /*!
     * @brief This function returns the value of member threshold
     * @return Value of member threshold
     */
    eProsima_user_DllExport int32_t threshold() const
    {
        return m_threshold;
    }

    /*!
     * @brief This function returns a reference to member threshold
     * @return Reference to member threshold
     */
    eProsima_user_DllExport int32_t& threshold()
    {
        return m_threshold;
    }


    /*!
     * @brief This function sets a value in member intensity
     * @param _intensity New value for member intensity
     */
    eProsima_user_DllExport void intensity(
            int32_t _intensity)
    {
        m_intensity = _intensity;
    }

    /*!
     * @brief This function returns the value of member intensity
     * @return Value of member intensity
     */
    eProsima_user_DllExport int32_t intensity() const
    {
        return m_intensity;
    }

    /*!
     * @brief This function returns a reference to member intensity
     * @return Reference to member intensity
     */
    eProsima_user_DllExport int32_t& intensity()
    {
        return m_intensity;
    }


    /*!
     * @brief This function sets a value in member battery
     * @param _battery New value for member battery
     */
    eProsima_user_DllExport void battery(
            int32_t _battery)
    {
        m_battery = _battery;
    }

    /*!
     * @brief This function returns the value of member battery
     * @return Value of member battery
     */
    eProsima_user_DllExport int32_t battery() const
    {
        return m_battery;
    }

    /*!
     * @brief This function returns a reference to member battery
     * @return Reference to member battery
     */
    eProsima_user_DllExport int32_t& battery()
    {
        return m_battery;
    }


    /*!
     * @brief This function sets a value in member enable
     * @param _enable New value for member enable
     */
    eProsima_user_DllExport void enable(
            bool _enable)
    {
        m_enable = _enable;
    }

    /*!
     * @brief This function returns the value of member enable
     * @return Value of member enable
     */
    eProsima_user_DllExport bool enable() const
    {
        return m_enable;
    }

    /*!
     * @brief This function returns a reference to member enable
     * @return Reference to member enable
     */
    eProsima_user_DllExport bool& enable()
    {
        return m_enable;
    }



private:

    int32_t m_sec{0};
    float m_distance{0.0};
    int32_t m_threshold{0};
    int32_t m_intensity{0};
    int32_t m_battery{0};
    bool m_enable{false};

};

#endif // _FAST_DDS_GENERATED_TOFDATA_HPP_


