#ifndef ARGPARSE_ArgObjContainer_HDR
#define ARGPARSE_ArgObjContainer_HDR

#include "ArgParse/ArgObject.h"
#include "ArgParse/Argument.h"
#include "ArgParse/ArgScalar.h"
#include "ArgParse/ArgVector.h"


namespace ArgParse {
	//Need to forward declare this..
	class ArgGroup;

	class ArgObjContainer {
		public:
			ArgObjContainer(ArgObjContainer* parent = nullptr) {
				this->parent = parent;
			}
			virtual ~ArgObjContainer();

			template<class T>
			void AddArgument(const std::string& call_name, const std::string& help_text, T* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = nullptr) {
				Argument* the_argument = (Argument*) new ArgScalar<T>(call_name, help_text, argument, required, was_defined);
				AddArgument(the_argument);
			}

			template<class T>
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<T>* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = nullptr) {
				Argument* the_argument = (Argument*) new ArgVector<T>(call_name, help_text, argument, required, was_defined);
				AddArgument(the_argument);
			}

			ArgGroup* AddArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);
			ArgGroup* AddInclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);
			ArgGroup* AddExclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);

		private:
			void CheckName(const std::string& call_name, ArgObjContainer* parent);
			void AddArgument(Argument* argument);
			void AddArgGroupObject(ArgGroup* arggroup);
			void AddArgObject(ArgObject* object);

		protected:
			ArgObjContainer* parent;
			std::vector<ArgObject*> objects;
	};
}

#endif
