#ifndef MEMKNAPP_H
#define MEMKNAPP_H

#include "Knapp.h"
#include <string>
namespace cwing{

	template <typename K>
	class MemKnapp : public Knapp{
	public:
		static MemKnapp* getInstance(int, int, std::string,K*, 
				void(K::*f)(std::string));
		void perform();
	protected:
		MemKnapp(int x, int y, std::string t,K* v, 
				void(K::*f)(std::string))
				: Knapp(x,y,t),objPek(v), mf(f){
		}
	private:
		K* objPek;
		void(K::*mf)(std::string);
	};

	template <typename K>
	MemKnapp<K>* MemKnapp<K>::getInstance(int x, int y, 
			std::string t, K* k,  void(K::*f)(std::string)){
		return new MemKnapp<K>(x,y,t,k,f);
	}

	template <typename T>
	void MemKnapp<T>::perform(){
			(objPek->*mf)(getText());
	}

} //namespace
#endif