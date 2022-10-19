#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/pc.h"
#include "winlua.h"

#include <locale.h>
#include <io.h>
#ifdef _WIN_LUAJIT_
extern PET pet[];
static int getPetData(lua_State *L) 
{
	const int id = luaL_checkint(L, 1);
	size_t l;
	const char *attribute=luaL_checklstring(L, 2, &l);
	
 	if(strcmp(attribute, "λ��") == 0){     
		lua_pushnumber(L, pet[id].index);
 	}else if(strcmp(attribute, "ͼ���") == 0){     
		lua_pushnumber(L, pet[id].graNo);
	}else if(strcmp(attribute, "HP") == 0){     
		lua_pushnumber(L, pet[id].hp);
	}else if(strcmp(attribute, "MaxHP") == 0){     
		lua_pushnumber(L, pet[id].maxHp);
	}else if(strcmp(attribute, "MP") == 0){     
		lua_pushnumber(L, pet[id].graNo);
	}else if(strcmp(attribute, "MaxMP") == 0){     
		lua_pushnumber(L, pet[id].graNo);
	}else if(strcmp(attribute, "����") == 0){     
		lua_pushnumber(L, pet[id].exp);
	}else if(strcmp(attribute, "�����") == 0){     
		lua_pushnumber(L, pet[id].maxExp);
	}else if(strcmp(attribute, "�ȼ�") == 0){     
		lua_pushnumber(L, pet[id].level);
	}else if(strcmp(attribute, "������") == 0){     
		lua_pushnumber(L, pet[id].atk);
	}else if(strcmp(attribute, "������") == 0){     
		lua_pushnumber(L, pet[id].def);
	}else if(strcmp(attribute, "������") == 0){     
		lua_pushnumber(L, pet[id].quick);
	}else if(strcmp(attribute, "�ҳ�") == 0){     
		lua_pushnumber(L, pet[id].ai);
	}else if(strcmp(attribute, "��") == 0){     
		lua_pushnumber(L, pet[id].earth);
	}else if(strcmp(attribute, "ˮ") == 0){     
		lua_pushnumber(L, pet[id].water);
	}else if(strcmp(attribute, "��") == 0){     
		lua_pushnumber(L, pet[id].fire);
	}else if(strcmp(attribute, "��") == 0){     
		lua_pushnumber(L, pet[id].wind);
	}else if(strcmp(attribute, "�������") == 0){     
		lua_pushnumber(L, pet[id].maxSkill);
	}else if(strcmp(attribute, "ת��") == 0){     
		lua_pushnumber(L, pet[id].trn);
	}else if(strcmp(attribute, "���ֱ���") == 0){     
		lua_pushnumber(L, pet[id].fusion);
	}else if(strcmp(attribute, "״̬") == 0){     
		lua_pushnumber(L, pet[id].status);
	}else if(strcmp(attribute, "����") == 0){     
		lua_pushstring(L, pet[id].name);
	}else if(strcmp(attribute, "�ǳ�") == 0){     
		lua_pushstring(L, pet[id].freeName);
	}else if(strcmp(attribute, "ʹ�����") == 0){     
		lua_pushnumber(L, pet[id].useFlag);
	}else if(strcmp(attribute, "������ʶ") == 0){     
		lua_pushnumber(L, pet[id].changeNameFlag);
	}     
	return 1;
}


static const luaL_Reg Datalib[] = {
	{"pet",					getPetData},
	{NULL,					NULL}
};

LUALIB_API int luaopen_Data (lua_State *L) {
	luaL_register(L, "chardata", Datalib);
	return 1;
}
#endif


