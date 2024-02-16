# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message(STATUS "${ASAP_LOG_PROJECT_HIERARCHY} >> third-party modules")

# Call `asap_add_package` to add third party packages using CPM, while
# automatically adding/removing them to the project hierarchy stack.
#
# Refer to https://github.com/cpm-cmake/CPM.cmake for the full usage.
#
# Example:
# ~~~
# asap_add_package(
#   NAME
#   magic_enum
#   GIT_TAG
#   master
#   GITHUB_REPOSITORY
#   abdes/magic_enum
#   OPTIONS
#   "MAGIC_ENUM_OPT_INSTALL ON")
# ~~~

# ------------------------------------------------------------------------------
# asap::common
# ------------------------------------------------------------------------------

asap_add_package(
  NAME
  asap_common
  GIT_TAG
  master
  GITHUB_REPOSITORY
  asap-projects/asap-common
  OPTIONS
  "ASAP_COMMON_INSTALL ON"
  "ASAP_BUILD_TESTS OFF"
  "ASAP_BUILD_EXAMPLES OFF")

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

asap_add_package(NAME gsl GIT_TAG main GITHUB_REPOSITORY microsoft/GSL)

# ------------------------------------------------------------------------------
# fmtlib
# ------------------------------------------------------------------------------

asap_add_package(
  NAME
  fmtlib
  GIT_TAG
  10.2.1
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "FMT_INSTALL ON")

# ------------------------------------------------------------------------------
# spdlog
# ------------------------------------------------------------------------------

asap_add_package(
  NAME
  spdlog
  GIT_TAG
  v1.13.0
  GITHUB_REPOSITORY
  gabime/spdlog
  OPTIONS
  "SPDLOG_BUILD_SHARED ON"
  "SPDLOG_INSTALL ON"
  "SPDLOG_FMT_EXTERNAL ON")
message(STATUS "${ASAP_LOG_PROJECT_HIERARCHY} >> third-party modules")
