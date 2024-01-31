# Note: when executed in the build dir, then CMAKE_CURRENT_SOURCE_DIR is the
# build dir.
file(COPY playground DESTINATION "${CMAKE_ARGV3}"
     FILES_MATCHING PATTERN "*.py"
                    PATTERN "*.pyi"
                    PATTERN "*.pyw"
                    PATTERN "*.pxi"
                    PATTERN "*.pxd"
                    PATTERN "*.toml"
                    )
