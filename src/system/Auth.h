#pragma once
#include <string>
#include <optional>
#include <pwd.h>
#include <vector>

namespace gush {
/**
 * Provides functions for retrieving users and groups information.
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
     * Retrieve information about process privileges
     */
    namespace Process {
      /**
       * Gets real user id of the process and returns info about that user
       */
      User get_real_user();

      /**
       * Gets real group if of the process and returns info about that group
       */
      Group get_real_group();

      /**
       * Gets effective user id of the process and returns info about that user
       */
      User get_effective_user();

      /**
       * Get effective group id of the process and returns info about that group
       */
      Group get_effective_group();

      /**
       * Sets effective user id to the id of the specified user
       * @param user - user with required user id
       * @return true if effective user id is changed successfully
       */
      bool set_effective_user(const User &user);

      /**
       * Set effective group id to the id of the specified group
       * @param group - group with required group id
       * @return true if effective group id is changed successfully
       */
      bool set_effective_group(const Group &group);

      /**
       * Sets effective user id for unprivileged user and sets effective/real/saved user id
       * for privileged user (root).
       *
       * @return true if user id is changed for that process
       */
      bool set_user(const User &user);

      /**
       * Sets effective group id for unprivileged user and sets effective/real/saved group id
       * for privileged user (root).
       *
       * @return true if group id is changed for that process
       */
      bool set_group(const Group &group);
    }

    /**
     * Returns user information by username
     * @param name - username
     * @return user information
     */
    std::optional<User> get_user(const std::string &name);

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
    std::optional<Group> get_group(const std::string &name);

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
     * Read a user password from the terminal
     * @param prompt - prompt for that password
     * @return returns a password
     */
    std::string read_password(const std::string &prompt);

  }
}