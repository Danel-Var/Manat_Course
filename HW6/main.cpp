
#include "ip.h"
#include "port.h"
#include "input.h"

#define SRC_IP_S "src-ip"
#define DST_IP_S "dst-ip"
#define SRC_PORT_S "src-port"
#define DST_PORT_S "dst-port"



bool is_ip_rule(const GenericString &type);
//bool rule_type(String& rule, String& type, String& value);

/**
 * @brief check if the arguments are valid packets, afterwards parse the stdin
 *        and leave only packets that match the given rule.
 * @param argc the number of arguments
 * @param argv the arguments
 * @return 0 if the arguments are valid, 1 otherwise
*/
int main(int argc, char **argv)
{
    //check if it is ip or port rule
    GenericString* rule = make_string(argv[1]);
    if(is_ip_rule(*rule)){
        IP ip_rule= IP(*rule);
        GenericField& send_rule = ip_rule;
        parse_input(send_rule);

    }else{
        //setting the rule
        Port port_rule= Port(*rule);
        
        GenericField& send_rule = port_rule;
        parse_input(send_rule);
        
    }
    /*
    const char* str_rule= "des-port=22-22";
    GenericString* rule =make_string(str_rule);
    Port my_port= Port(*rule);
    */

   
    return 0;
}

bool is_ip_rule(const GenericString &type){
    const String& str =type.as_string();
    String str_c=String(str);
    GenericString* value_c = &(str_c.trim());

    StringArray my_type= (value_c->as_string()).split("=");
    value_c =my_type[0];
    value_c = &(value_c->as_string()).trim();
    return ((value_c->as_string() == SRC_IP_S ||
             value_c->as_string() == DST_IP_S));
}
