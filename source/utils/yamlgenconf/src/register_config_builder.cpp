
#include "register_config_builder.hpp"
#include "config_node.hpp"
#include "register_config.hpp"
#include "register_group_config.hpp"
#include "abstract_config_runner.hpp"
#include "abstract_register_config_runner.hpp"
#include "exception/generator_exception.hpp"

void
RegisterConfigBuilder::parse(Interpreter const & interpreter)
throw (GeneratorException)
{
	ConfigNode root;
	ConfigNode config = interpreter.config(); 
	ConfigNode::const_iterator root_it = config.find("config_root");
	if(root_it != config.end()) { 
		root = (*root_it).second;
	}
	else { 
		throw GeneratorException("Could not find config_root");
	}
	
	ConfigNode::const_iterator it_groups  = root.begin(); 
	ConfigNode::const_iterator end_groups = root.end(); 
	for(; it_groups != end_groups; ++it_groups) { 
		RegisterGroupConfig group = RegisterGroupConfig((*it_groups).first);
		
		ConfigNode group_config = (*it_groups).second; 
		group.set_properties(group_config.values());
		
		ConfigNode registers = (*it_groups).second; 
		ConfigNode::const_iterator reglist = registers.find("registers"); 
		ConfigNode register_list = (*reglist).second; 
		
		ConfigNode::const_iterator it_regs  = register_list.begin(); 
		ConfigNode::const_iterator end_regs = register_list.end(); 
		
		for(; it_regs != end_regs; ++it_regs) { 
			RegisterConfig reg = RegisterConfig((*it_regs).first);
			ConfigNode properties = (*it_regs).second; 
			reg.set_properties(properties.values());
			group.add_register(reg); 
		}
		m_register_groups.push_back(group);
		group.log(); 
	}
}

void 
RegisterConfigBuilder::run(AbstractRegisterConfigRunner & runner) throw (RunnerException) {
	runner.run(this); 
}
