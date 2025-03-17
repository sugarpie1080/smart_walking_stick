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
 * @file ToFDataCdrAux.ipp
 * This source file contains some declarations of CDR related functions.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef FAST_DDS_GENERATED__TOFDATACDRAUX_IPP
#define FAST_DDS_GENERATED__TOFDATACDRAUX_IPP

#include "ToFDataCdrAux.hpp"

#include <fastcdr/Cdr.h>
#include <fastcdr/CdrSizeCalculator.hpp>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

namespace eprosima {
namespace fastcdr {

template<>
eProsima_user_DllExport size_t calculate_serialized_size(
        eprosima::fastcdr::CdrSizeCalculator& calculator,
        const ToFData& data,
        size_t& current_alignment)
{
    static_cast<void>(data);

    eprosima::fastcdr::EncodingAlgorithmFlag previous_encoding = calculator.get_encoding();
    size_t calculated_size {calculator.begin_calculate_type_serialized_size(
                                eprosima::fastcdr::CdrVersion::XCDRv2 == calculator.get_cdr_version() ?
                                eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
                                eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
                                current_alignment)};


        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(0),
                data.sec(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(1),
                data.distance(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(2),
                data.threshold(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(3),
                data.intensity(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(4),
                data.battery(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(5),
                data.enable(), current_alignment);


    calculated_size += calculator.end_calculate_type_serialized_size(previous_encoding, current_alignment);

    return calculated_size;
}

template<>
eProsima_user_DllExport void serialize(
        eprosima::fastcdr::Cdr& scdr,
        const ToFData& data)
{
    eprosima::fastcdr::Cdr::state current_state(scdr);
    scdr.begin_serialize_type(current_state,
            eprosima::fastcdr::CdrVersion::XCDRv2 == scdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);

    scdr
        << eprosima::fastcdr::MemberId(0) << data.sec()
        << eprosima::fastcdr::MemberId(1) << data.distance()
        << eprosima::fastcdr::MemberId(2) << data.threshold()
        << eprosima::fastcdr::MemberId(3) << data.intensity()
        << eprosima::fastcdr::MemberId(4) << data.battery()
        << eprosima::fastcdr::MemberId(5) << data.enable()
;
    scdr.end_serialize_type(current_state);
}

template<>
eProsima_user_DllExport void deserialize(
        eprosima::fastcdr::Cdr& cdr,
        ToFData& data)
{
    cdr.deserialize_type(eprosima::fastcdr::CdrVersion::XCDRv2 == cdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
            [&data](eprosima::fastcdr::Cdr& dcdr, const eprosima::fastcdr::MemberId& mid) -> bool
            {
                bool ret_value = true;
                switch (mid.id)
                {
                                        case 0:
                                                dcdr >> data.sec();
                                            break;

                                        case 1:
                                                dcdr >> data.distance();
                                            break;

                                        case 2:
                                                dcdr >> data.threshold();
                                            break;

                                        case 3:
                                                dcdr >> data.intensity();
                                            break;

                                        case 4:
                                                dcdr >> data.battery();
                                            break;

                                        case 5:
                                                dcdr >> data.enable();
                                            break;

                    default:
                        ret_value = false;
                        break;
                }
                return ret_value;
            });
}

void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const ToFData& data)
{

    static_cast<void>(scdr);
    static_cast<void>(data);
                        scdr << data.sec();

                        scdr << data.distance();

                        scdr << data.threshold();

                        scdr << data.intensity();

                        scdr << data.battery();

                        scdr << data.enable();

}



} // namespace fastcdr
} // namespace eprosima

#endif // FAST_DDS_GENERATED__TOFDATACDRAUX_IPP

