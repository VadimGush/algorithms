#include <string>
#include <optional>

/**
 * Provides simple functions to work with environment variables.
 */
namespace Environment {

  /**
   * Returns a value of an environment variable
   * @param name - name of the variable
   * @return value of the variable
   */
  std::optional<std::string> get(const std::string& name);

  /**
   * Set an environment variable to the specified value
   * @param name - name of the variable
   * @param value - new value for that variable
   */
  void set(const std::string& name, const std::string& value);

};
