#include <cassert>
#include <cstdlib>
#include <iostream>
#include "include/config.hpp"
#include "include/logger.hpp"

using namespace pg_ai::config;

void test_env_vars() {
  std::cout << "Testing environment variables..." << std::endl;

  // Set environment variables
  setenv("OPENAI_API_KEY", "sk-test-openai-key", 1);
  setenv("ANTHROPIC_API_KEY", "sk-test-anthropic-key", 1);

  // Load config (this should pick up env vars)
  ConfigManager::loadConfig("non_existent_file.config");

  // Check OpenAI key
  auto openai_config = ConfigManager::getProviderConfig(Provider::OPENAI);
  assert(openai_config != nullptr);
  assert(openai_config->api_key == "sk-test-openai-key");
  std::cout << "OpenAI API key loaded correctly from env." << std::endl;

  // Check Anthropic key
  auto anthropic_config = ConfigManager::getProviderConfig(Provider::ANTHROPIC);
  assert(anthropic_config != nullptr);
  assert(anthropic_config->api_key == "sk-test-anthropic-key");
  std::cout << "Anthropic API key loaded correctly from env." << std::endl;

  // Clean up
  unsetenv("OPENAI_API_KEY");
  unsetenv("ANTHROPIC_API_KEY");
}

int main() {
  // Disable logging for clean output
  pg_ai::logger::Logger::setLoggingEnabled(false);

  test_env_vars();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
