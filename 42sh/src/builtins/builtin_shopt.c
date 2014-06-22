#include "builtins.h"

static int check_opt(s_simple_cmd *cmd)
{
  int opt = NO_OPT;

  if (!strcmp(cmd->element[1]->element.word, "-s"))
    opt = S_OPT;

  if (!strcmp(cmd->element[1]->element.word, "-u"))
    opt = U_OPT;

  if (!strcmp(cmd->element[1]->element.word, "-q"))
    opt = Q_OPT;

  return opt;
}

static int ast_print(int opt)
{
  int res;
  opt = opt;
  return res;
}

static int dot_glob(int opt)
{
  int res;
  opt = opt;
  //42sh includes filenames beginning with a ‘.’ in filename expansion.
  return res;
}

static int expand_aliases(int opt)
{
  int res;
  opt = opt;
  //aliases are expanded as described below under Aliases
  return res;
}

static int extglob(int opt)
{
  int res;
  opt = opt;
  //the extended pattern matching features described above are enabled.
  return res;
}

static int nocaseglob(int opt)
{
  int res;
  opt = opt;
  //42sh matches filenames in a case-insensitive
  //fashion when performing filename expansion.
  return res;
}

static int nullglob(int opt)
{
  int res;
  opt = opt;
  //42sh allows filename patterns which match no
  //files to expand to a null string, rather than themselves
  return res;
}

static int sourcepath(int opt)
{
  int res;
  opt = opt;
  //the source builtin uses the value of PATH to
  //find the directory containing the file supplied as an argument
  return res;
}

static int xpg_echo(int opt)
{
  int res;
  opt = opt;
  //the echo builtin expands backslash-escape sequences by default
  //set_builtin_echo(cmd, 1);
  return res;
}

int builtin_shopt(s_simple_cmd *cmd)
{
  int opt = NO_OPT;
  int res = 1;

  opt = check_opt(cmd);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "ast_print"))
    res = ast_print(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "dot_glob"))
    res = dot_glob(opt);

  if (cmd->element[2] &&
      !strcmp(cmd->element[2]->element.word, "expand_aliases"))
    res = expand_aliases(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "extglob"))
    res = extglob(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "nocaseglob"))
    res = nocaseglob(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "nullglob"))
    res = nullglob(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "sourcepath"))
    res = sourcepath(opt);

  if (cmd->element[2] && !strcmp(cmd->element[2]->element.word, "xpg_echo"))
    res = xpg_echo(opt);

  return res;
}
