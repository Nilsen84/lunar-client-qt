file(GLOB _file_list "${src_dir}/*")

file(MAKE_DIRECTORY ${dst_dir})

foreach(src_file ${_file_list})
    get_filename_component(new_file_name ${src_file} NAME_WE)
    set(dst_file "${dst_dir}/${new_file_name}")
    file(COPY_FILE ${src_file} ${dst_file} ONLY_IF_DIFFERENT)
endforeach()