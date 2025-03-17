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
 * @file ToFDataTypeObjectSupport.cxx
 * Source file containing the implementation to register the TypeObject representation of the described types in the IDL file
 *
 * This file was generated by the tool fastddsgen.
 */

#include "ToFDataTypeObjectSupport.hpp"

#include <mutex>
#include <string>

#include <fastcdr/xcdr/external.hpp>
#include <fastcdr/xcdr/optional.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/log/Log.hpp>
#include <fastdds/dds/xtypes/common.hpp>
#include <fastdds/dds/xtypes/type_representation/ITypeObjectRegistry.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObject.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObjectUtils.hpp>

#include "ToFData.hpp"


using namespace eprosima::fastdds::dds::xtypes;

// TypeIdentifier is returned by reference: dependent structures/unions are registered in this same method
void register_ToFData_type_identifier(
        TypeIdentifierPair& type_ids_ToFData)
{

    ReturnCode_t return_code_ToFData {eprosima::fastdds::dds::RETCODE_OK};
    return_code_ToFData =
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
        "ToFData", type_ids_ToFData);
    if (eprosima::fastdds::dds::RETCODE_OK != return_code_ToFData)
    {
        StructTypeFlag struct_flags_ToFData = TypeObjectUtils::build_struct_type_flag(eprosima::fastdds::dds::xtypes::ExtensibilityKind::APPENDABLE,
                false, false);
        QualifiedTypeName type_name_ToFData = "ToFData";
        eprosima::fastcdr::optional<AppliedBuiltinTypeAnnotations> type_ann_builtin_ToFData;
        eprosima::fastcdr::optional<AppliedAnnotationSeq> ann_custom_ToFData;
        CompleteTypeDetail detail_ToFData = TypeObjectUtils::build_complete_type_detail(type_ann_builtin_ToFData, ann_custom_ToFData, type_name_ToFData.to_string());
        CompleteStructHeader header_ToFData;
        header_ToFData = TypeObjectUtils::build_complete_struct_header(TypeIdentifier(), detail_ToFData);
        CompleteStructMemberSeq member_seq_ToFData;
        {
            TypeIdentifierPair type_ids_sec;
            ReturnCode_t return_code_sec {eprosima::fastdds::dds::RETCODE_OK};
            return_code_sec =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_int32_t", type_ids_sec);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_sec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "sec Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_sec = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_sec = 0x00000000;
            bool common_sec_ec {false};
            CommonStructMember common_sec {TypeObjectUtils::build_common_struct_member(member_id_sec, member_flags_sec, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_sec, common_sec_ec))};
            if (!common_sec_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure sec member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_sec = "sec";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_sec;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_sec = TypeObjectUtils::build_complete_member_detail(name_sec, member_ann_builtin_sec, ann_custom_ToFData);
            CompleteStructMember member_sec = TypeObjectUtils::build_complete_struct_member(common_sec, detail_sec);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_sec);
        }
        {
            TypeIdentifierPair type_ids_distance;
            ReturnCode_t return_code_distance {eprosima::fastdds::dds::RETCODE_OK};
            return_code_distance =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_float", type_ids_distance);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_distance)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "distance Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_distance = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_distance = 0x00000001;
            bool common_distance_ec {false};
            CommonStructMember common_distance {TypeObjectUtils::build_common_struct_member(member_id_distance, member_flags_distance, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_distance, common_distance_ec))};
            if (!common_distance_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure distance member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_distance = "distance";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_distance;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_distance = TypeObjectUtils::build_complete_member_detail(name_distance, member_ann_builtin_distance, ann_custom_ToFData);
            CompleteStructMember member_distance = TypeObjectUtils::build_complete_struct_member(common_distance, detail_distance);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_distance);
        }
        {
            TypeIdentifierPair type_ids_threshold;
            ReturnCode_t return_code_threshold {eprosima::fastdds::dds::RETCODE_OK};
            return_code_threshold =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_int32_t", type_ids_threshold);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_threshold)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "threshold Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_threshold = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_threshold = 0x00000002;
            bool common_threshold_ec {false};
            CommonStructMember common_threshold {TypeObjectUtils::build_common_struct_member(member_id_threshold, member_flags_threshold, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_threshold, common_threshold_ec))};
            if (!common_threshold_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure threshold member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_threshold = "threshold";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_threshold;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_threshold = TypeObjectUtils::build_complete_member_detail(name_threshold, member_ann_builtin_threshold, ann_custom_ToFData);
            CompleteStructMember member_threshold = TypeObjectUtils::build_complete_struct_member(common_threshold, detail_threshold);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_threshold);
        }
        {
            TypeIdentifierPair type_ids_intensity;
            ReturnCode_t return_code_intensity {eprosima::fastdds::dds::RETCODE_OK};
            return_code_intensity =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_int32_t", type_ids_intensity);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_intensity)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "intensity Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_intensity = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_intensity = 0x00000003;
            bool common_intensity_ec {false};
            CommonStructMember common_intensity {TypeObjectUtils::build_common_struct_member(member_id_intensity, member_flags_intensity, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_intensity, common_intensity_ec))};
            if (!common_intensity_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure intensity member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_intensity = "intensity";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_intensity;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_intensity = TypeObjectUtils::build_complete_member_detail(name_intensity, member_ann_builtin_intensity, ann_custom_ToFData);
            CompleteStructMember member_intensity = TypeObjectUtils::build_complete_struct_member(common_intensity, detail_intensity);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_intensity);
        }
        {
            TypeIdentifierPair type_ids_battery;
            ReturnCode_t return_code_battery {eprosima::fastdds::dds::RETCODE_OK};
            return_code_battery =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_int32_t", type_ids_battery);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_battery)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "battery Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_battery = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_battery = 0x00000004;
            bool common_battery_ec {false};
            CommonStructMember common_battery {TypeObjectUtils::build_common_struct_member(member_id_battery, member_flags_battery, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_battery, common_battery_ec))};
            if (!common_battery_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure battery member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_battery = "battery";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_battery;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_battery = TypeObjectUtils::build_complete_member_detail(name_battery, member_ann_builtin_battery, ann_custom_ToFData);
            CompleteStructMember member_battery = TypeObjectUtils::build_complete_struct_member(common_battery, detail_battery);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_battery);
        }
        {
            TypeIdentifierPair type_ids_enable;
            ReturnCode_t return_code_enable {eprosima::fastdds::dds::RETCODE_OK};
            return_code_enable =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_bool", type_ids_enable);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_enable)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "enable Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_enable = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_enable = 0x00000005;
            bool common_enable_ec {false};
            CommonStructMember common_enable {TypeObjectUtils::build_common_struct_member(member_id_enable, member_flags_enable, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_enable, common_enable_ec))};
            if (!common_enable_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure enable member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_enable = "enable";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_enable;
            ann_custom_ToFData.reset();
            CompleteMemberDetail detail_enable = TypeObjectUtils::build_complete_member_detail(name_enable, member_ann_builtin_enable, ann_custom_ToFData);
            CompleteStructMember member_enable = TypeObjectUtils::build_complete_struct_member(common_enable, detail_enable);
            TypeObjectUtils::add_complete_struct_member(member_seq_ToFData, member_enable);
        }
        CompleteStructType struct_type_ToFData = TypeObjectUtils::build_complete_struct_type(struct_flags_ToFData, header_ToFData, member_seq_ToFData);
        if (eprosima::fastdds::dds::RETCODE_BAD_PARAMETER ==
                TypeObjectUtils::build_and_register_struct_type_object(struct_type_ToFData, type_name_ToFData.to_string(), type_ids_ToFData))
        {
            EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                    "ToFData already registered in TypeObjectRegistry for a different type.");
        }
    }
}

