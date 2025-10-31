function(autogen_assets TARGET_NAME RESOURCES_DIR)

  get_filename_component(RESOURCES_DIR_ABS "${RESOURCES_DIR}" ABSOLUTE)

  if(NOT EXISTS "${RESOURCES_DIR_ABS}")
    message(FATAL_ERROR "Resources directory does not exist: ${RESOURCES_DIR_ABS}")
  endif()

  file(GLOB_RECURSE RESOURCE_FILES "${RESOURCES_DIR_ABS}/*")
  set(FILTERED_FILES)

  foreach(FILE ${RESOURCE_FILES})
    if(NOT IS_DIRECTORY "${FILE}")
      list(APPEND FILTERED_FILES "${FILE}")
    endif()
  endforeach()

  if(NOT FILTERED_FILES)
    message(WARNING "No resource files found in ${RESOURCES_DIR_ABS}")
  endif()

  set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
  set(ASSETS_DIR "${GENERATED_DIR}/assets")

  file(MAKE_DIRECTORY "${ASSETS_DIR}")

  set(GENERATED_CPP_FILE "${ASSETS_DIR}/assets.cpp")
  set(GENERATED_HPP_FILE "${ASSETS_DIR}/assets.hpp")

  file(WRITE "${GENERATED_HPP_FILE}" "#pragma once\n\n")
  file(APPEND "${GENERATED_HPP_FILE}" "#include <vector>\n")
  file(APPEND "${GENERATED_HPP_FILE}" "#include <string>\n")
  file(APPEND "${GENERATED_HPP_FILE}" "#include <cstdint>\n\n")
  file(APPEND "${GENERATED_HPP_FILE}" "namespace assets {\n")
  file(APPEND "${GENERATED_HPP_FILE}" "    std::vector<uint8_t> load(const std::string& path);\n")
  file(APPEND "${GENERATED_HPP_FILE}" "}\n")

  file(WRITE "${GENERATED_CPP_FILE}" "#include \"assets.hpp\"\n\n")
  file(APPEND "${GENERATED_CPP_FILE}" "#include <iostream>\n")
  file(APPEND "${GENERATED_CPP_FILE}" "#include <array>\n\n")
  file(APPEND "${GENERATED_CPP_FILE}" "namespace assets {\n\n")

  if(FILTERED_FILES)
    set(ASSET_DECLARATIONS "")
    set(ENTRIES_ARRAY "")

    foreach(RESOURCE_FILE ${FILTERED_FILES})
      file(RELATIVE_PATH REL_PATH "${RESOURCES_DIR_ABS}" "${RESOURCE_FILE}")
      file(READ "${RESOURCE_FILE}" FILE_CONTENT HEX)
      string(LENGTH "${FILE_CONTENT}" HEX_LENGTH)
      math(EXPR FILE_SIZE "${HEX_LENGTH} / 2")

      if(FILE_SIZE GREATER 0)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "_" SAFE_NAME "${REL_PATH}")
        string(TOUPPER "${SAFE_NAME}" SAFE_NAME)

        string(APPEND ASSET_DECLARATIONS "static constexpr uint8_t ASSET_${SAFE_NAME}[] = {\n")
        string(REGEX REPLACE "(..)" "0x\\1, " BYTE_ARRAY "${FILE_CONTENT}")
        string(REGEX REPLACE ", $" "" BYTE_ARRAY "${BYTE_ARRAY}")
        string(REGEX REPLACE "(.{48})" "\\1\n    " FORMATTED_BYTES "${BYTE_ARRAY}")
        string(APPEND ASSET_DECLARATIONS "    ${FORMATTED_BYTES}\n")
        string(APPEND ASSET_DECLARATIONS "};\n\n")

        string(REPLACE "\\" "/" RESOURCE_PATH "/${REL_PATH}")
        string(APPEND ENTRIES_ARRAY "    {\"${RESOURCE_PATH}\", ASSET_${SAFE_NAME}, ${FILE_SIZE}}")

        list(GET FILTERED_FILES -1 LAST_FILE)

        if(NOT RESOURCE_FILE STREQUAL LAST_FILE)
          string(APPEND ENTRIES_ARRAY ",\n")
        endif()

      endif()
    endforeach()

    list(LENGTH FILTERED_FILES RESOURCE_COUNT)

    file(APPEND "${GENERATED_CPP_FILE}" "struct AssetEntry {\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    const char* path;\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    const uint8_t* data;\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    size_t size;\n")
    file(APPEND "${GENERATED_CPP_FILE}" "};\n\n")

    file(APPEND "${GENERATED_CPP_FILE}" "${ASSET_DECLARATIONS}")
    
    file(APPEND "${GENERATED_CPP_FILE}" "static constexpr std::array<AssetEntry, ${RESOURCE_COUNT}> ASSETS = {{\n")
    file(APPEND "${GENERATED_CPP_FILE}" "${ENTRIES_ARRAY}\n")
    file(APPEND "${GENERATED_CPP_FILE}" "}};\n\n")

    file(APPEND "${GENERATED_CPP_FILE}" "std::vector<uint8_t> load(const std::string& path) {\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    for (const auto& asset : ASSETS) {\n")
    file(APPEND "${GENERATED_CPP_FILE}" "        if (asset.path == path) {\n")
    file(APPEND "${GENERATED_CPP_FILE}" "            return {asset.data, asset.data + asset.size};\n")
    file(APPEND "${GENERATED_CPP_FILE}" "        }\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    }\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    std::cerr << \"Autogen-Assets: [ERROR] - Asset not found: \" << path << std::endl;\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    return {};\n")
    file(APPEND "${GENERATED_CPP_FILE}" "}\n\n")

  else()
    file(APPEND "${GENERATED_CPP_FILE}" "std::vector<uint8_t> load(const std::string& path) {\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    std::cerr << \"Autogen-Assets: [ERROR] - No assets available, path requested: \" << path << std::endl;\n")
    file(APPEND "${GENERATED_CPP_FILE}" "    return {};\n")
    file(APPEND "${GENERATED_CPP_FILE}" "}\n\n")
    set(RESOURCE_COUNT 0)
  endif()

  file(APPEND "${GENERATED_CPP_FILE}" "} // namespace assets\n")

  list(LENGTH FILTERED_FILES RESOURCE_COUNT)
  target_sources(${TARGET_NAME} PRIVATE "${GENERATED_CPP_FILE}")
  target_include_directories(${TARGET_NAME} PRIVATE "${GENERATED_DIR}")
  set_property(TARGET ${TARGET_NAME} APPEND PROPERTY OBJECT_DEPENDS ${FILTERED_FILES})

  message(STATUS "Autogen-Assets: [INFO] - Generated ${RESOURCE_COUNT} assets for ${TARGET_NAME}")

endfunction()
