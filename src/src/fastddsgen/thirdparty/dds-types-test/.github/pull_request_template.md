<!-- Provide a general summary of your changes in the Title above -->
<!-- It must be meaningful and coherent with the changes -->

<!--
    If this PR is still a Work in Progress [WIP], please open it as DRAFT.
    Please consider if any label should be added to this PR.
-->

## Description
<!--
    Describe changes in detail.
    This includes depicting the context, use case or current behavior and describe the proposed changes.
-->

## Contributor Checklist
- [ ] Commit messages follow the project guidelines. <!-- External contributors should sign the DCO. Fast DDS developers must also refer to the internal Redmine task. -->
- [ ] Any new/modified type has been properly reflected on `test/feature/dynamic_types/dds_types_tests` tests in a Pull Request. <!-- It is mandatory to test new/modified tests with the Dynamic Type API -->
- [ ] Any new/modified type has been properly updated on `test/dds/xtypes` tests using `update_header_and_create_cases.py` script in a Pull Request. <!-- It is mandatory to update the test source code using the script -->
- [ ] For any new IDL file, Fast DDS `update_generated_code_from_idl.sh` script adding a new line in `file_needing_output_dir` list in a Pull Request. <!-- It is mandatory to generate always the code for new IDL files -->

## Reviewer Checklist
- [ ] The PR has a milestone assigned.
- [ ] The title and description correctly express the PR's purpose.
- [ ] Check contributor checklist is correct.
