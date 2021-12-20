#include "Auth.h"
#include <grp.h>
#include <unistd.h>

static Auth::User get_user(const passwd* passwd) {
  return Auth::User {
      .name = std::string(passwd->pw_name),
      .password = std::string(passwd->pw_passwd),
      .uid = passwd->pw_uid,
      .gid = passwd->pw_gid,
      .comment = std::string(passwd->pw_gecos),
      .directory = std::string(passwd->pw_dir),
      .shell = std::string(passwd->pw_shell)
  };
}

static Auth::Group get_group(const group* group) {
  std::vector<std::string> users{};

  size_t id = 0;
  char* user = nullptr;
  while ((user = group->gr_mem[id]) != nullptr) {
    users.emplace_back(user);
    id++;
  }

  return Auth::Group {
    .name = std::string{group->gr_name},
    .id = group->gr_gid,
    .users = std::move(users)
  };
}

/*
static void print_get_group_error() {
  if (errno == 0) { error() << "Group not found" << ln; }
  else { with_errno() << "Failed to retrieve group information" << ln; }
}
 */

std::optional<Auth::Group> Auth::get_group(const gid_t gid) {
  const group* group = getgrgid(gid);
  if (group == nullptr) { return {}; }
  return get_group(group);
}

std::optional<Auth::Group> Auth::get_group(const std::string& name) {
  const group* group = getgrnam(name.c_str());
  if (group == nullptr) { return {}; }
  return get_group(group);
}

/*
static void print_get_user_error() {
  if (errno == 0) { error() << "User not found" << ln; }
  else { with_errno() << "Failed to retrieve user information" << ln; }
}
 */

std::optional<Auth::User> Auth::get_user(const uid_t uid) {
  const passwd* passwd = getpwuid(uid);

  if (passwd == nullptr) { return {}; }
  return get_user(passwd);
}

std::optional<Auth::User> Auth::get_user(const std::string& name) {
  const passwd* passwd = getpwnam(name.c_str());

  if (passwd == nullptr) { return {}; }
  return get_user(passwd);
}

std::vector<Auth::User> Auth::get_users() {
  std::vector<Auth::User> users{};

  passwd* user;
  while ((user = getpwent()) != nullptr) {
    users.push_back(get_user(user));
  }
  endpwent();

  return users;
}

std::string Auth::read_password(const std::string& prompt) {
  char* const plain_password = getpass(prompt.c_str());
  // copy password
  std::string password{plain_password};
  // clean plain password
  char* ptr = plain_password;
  while (*ptr != '\0') {
    *ptr = '\0';
    ptr += 1;
  }
  return std::move(password);
}

Auth::User Auth::Process::get_real_user() {
  return *Auth::get_user(getuid());
}

Auth::Group Auth::Process::get_real_group() {
  return *Auth::get_group(getgid());
};

Auth::User Auth::Process::get_effective_user() {
  return *Auth::get_user(geteuid());
}

Auth::Group Auth::Process::get_effective_group() {
  return *Auth::get_group(getegid());
}

bool Auth::Process::set_user(const User& user) {
  const auto status = setuid(user.uid);
  if (status != 0) { return false; }
  return true;
}

bool Auth::Process::set_group(const Group& group) {
  const auto status = setgid(group.id);
  if (status != 0) { return false; }
  return true;
}

