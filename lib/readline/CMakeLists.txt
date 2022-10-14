set(LOCAL_CFLAGS "-DRL_LIBRARY_VERSION='\"8.2\"' -DBRACKETED_PASTE_DEFAULT=1")
set(CFLAGS "-g -O2 -Wno-parentheses -Wno-format-security -Wno-tautological-constant-out-of-range-compare")
set(XCCFLAGS "-DHAVE_CONFIG_H -I.")
set(CMAKE_C_FLAGS "${XCCFLAGS} ${LOCAL_CFLAGS} ${CFLAGS}")

add_library(local_readline STATIC
  readline.c
  funmap.c
  keymaps.c
  vi_mode.c
  parens.c
  rltty.c
  complete.c
  bind.c
  parse-colors.c
  colors.c
  isearch.c
  display.c
  signals.c
  emacs_keymap.c
  vi_keymap.c
  util.c
  kill.c
  undo.c
  macro.c
  input.c
  callback.c
  terminal.c
  xmalloc.c
  xfree.c
  history.c
  histsearch.c
  histexpand.c
  histfile.c
  nls.c
  search.c
  shell.c
  savestring.c
  tilde.c
  text.c
  misc.c
  compat.c
  mbutil.c
  readline.h
  rldefs.h
  chardefs.h
  posixstat.h
  posixdir.h
  posixjmp.h
  tilde.h
  rlconf.h
  rltty.h
  ansi_stdlib.h
  tcap.h
  rlstdc.h
  xmalloc.h
  rlprivate.h
  rlshell.h
  rltypedefs.h
  rlmbutil.h
  colors.h
  parse-colors.h
  config.h
)

target_include_directories(local_readline PRIVATE ".")

if(UNIX)
  target_link_libraries(local_readline PRIVATE -ltinfo)
endif(UNIX)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/config.h COMMAND "./configure" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
