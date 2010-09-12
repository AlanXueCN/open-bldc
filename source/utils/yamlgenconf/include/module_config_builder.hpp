#ifndef MODULE_CONFIG_GENERATOR_STRATEGY_HPP__
#define MODULE_CONFIG_GENERATOR_STRATEGY_HPP__

#include "abstract_config_builder.hpp"
#include "exception/generator_exception.hpp"
#include "module_config_strategy.hpp"
#include "module_config.hpp"
#include <vector>


class ModuleConfigBuilder : public AbstractConfigBuilder<ModuleConfigStrategy>
{

private: 

	::std::vector<ModuleConfig> m_modules; 

public: 

	ModuleConfigBuilder() { } 
	virtual ~ModuleConfigBuilder() { } 

public: 

	virtual void parse(ConfigNode const & config) throw (GeneratorException); 
	virtual void parse_partial(ConfigNode const & config_node) throw (GeneratorException); 
	virtual void run(AbstractModuleConfigRunner & runner) throw (RunnerException);

public: 

	::std::vector<ModuleConfig> const & modules(void) const { return m_modules; }

};

#endif /* MODULE_CONFIG_GENERATOR_STRATEGY_HPP__ */
