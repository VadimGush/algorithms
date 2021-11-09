#pragma once
#include <string>
#include <optional>
#include <pwd.h>
#include <vector>

/**
 * Provides simple functions to work with authentication system
 */
namespace Auth {

  struct User {
    std::string name;
    std::string password;
    uid_t uid;
    gid_t gid;
    std::string comment;
    std::string directory;
    std::string shell;
  };

  struct Group {
    std::string name;
    gid_t id;
    std::vector<std::string> users;
  };

  /**
   * Returns user information by username
   * @param name - username
   * @return user information
   */
  std::optional<User> get_user(const std::string& name);

  /**
   * Returns user information by user id (uid)
   * @param uid - user id
   * @return user information
   */
  std::optional<User> get_user(uid_t uid);

  /**
   * Returns group information by name
   * @param name - group name
   * @return group information
   */
  std::optional<Group> get_group(const std::string& name);

  /**
   * Returns group information by group id (gid)
   * @param gid - group id
   * @return group information
   */
  std::optional<Group> get_group(gid_t gid);

  /**
   * Returns full list of users
   * @return all users from /etc/passwd file
   */
  std::vector<User> get_users();

  /**
   * Read a user password from terminal
   * @param prompt - prompt for that password
   * @return returns a password
   */
  std::string read_password(const std::string& prompt);

}