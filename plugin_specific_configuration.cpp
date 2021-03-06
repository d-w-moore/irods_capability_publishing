
#include "plugin_specific_configuration.hpp"
#include "irods_server_properties.hpp"
#include "irods_exception.hpp"

namespace irods {
    namespace publishing {
         plugin_specific_configuration get_plugin_specific_configuration(
            const std::string& _instance_name ) {
            try {
                const auto& rule_engines = get_server_property<
                    const std::vector<boost::any>&>(
                            std::vector<std::string>{
                            CFG_PLUGIN_CONFIGURATION_KW,
                            PLUGIN_TYPE_RULE_ENGINE});
                for ( const auto& elem : rule_engines ) {
                    const auto& rule_engine = boost::any_cast< const std::unordered_map< std::string, boost::any >& >( elem );
                    const auto& inst_name   = boost::any_cast< const std::string& >( rule_engine.at( CFG_INSTANCE_NAME_KW ) );
                    if ( inst_name == _instance_name ) {
                        if(rule_engine.count(CFG_PLUGIN_SPECIFIC_CONFIGURATION_KW) > 0) {
                            return boost::any_cast<const std::unordered_map<std::string, boost::any>&>(
                                    rule_engine.at(CFG_PLUGIN_SPECIFIC_CONFIGURATION_KW));
                        } // if has PSC
                    } // if inst_name
                } // for rule_engines
            } catch ( const boost::bad_any_cast& e ) {
                THROW( INVALID_ANY_CAST, e.what() );
            } catch ( const std::out_of_range& e ) {
                THROW( KEY_NOT_FOUND, e.what() );
            }

            THROW(
                SYS_INVALID_INPUT_PARAM,
                boost::format("failed to find configuration for publishing plugin [%s]") %
                _instance_name);
        } // get_plugin_specific_configuration


    } // namespace publishing
} // namespace irods
