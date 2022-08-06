# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message("=> [third-party modules]")

# ------------------------------------------------------------------------------
# asap::common
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  asap_common
  GIT_TAG
  master
  GITHUB_REPOSITORY
  asap-projects/asap-common
  OPTIONS
  "ASAP_COMMON_INSTALL ON"
)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  gsl
  GIT_TAG
  main
  GITHUB_REPOSITORY
  microsoft/GSL
)

# ------------------------------------------------------------------------------
# fmtlib
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  fmtlib
  GIT_TAG
  9.0.0
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "FMT_INSTALL ON")

# ------------------------------------------------------------------------------
# spdlog
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  spdlog
  GIT_TAG
  v1.10.0
  GITHUB_REPOSITORY
  gabime/spdlog
  OPTIONS
  "SPDLOG_BUILD_SHARED ON"
  "SPDLOG_INSTALL ON"
  "SPDLOG_FMT_EXTERNAL ON"
  )
