﻿#include "Module.h"
#include "NBT.h"

using namespace std;
//是否为史莱姆区块
constexpr int IsSlimeChunk(unsigned x, unsigned z) {
	unsigned mt0 = (x * 0x1F1F1F1F) ^ z;
	unsigned mt1 = (1812433253u * (mt0 ^ (mt0 >> 30u)) + 1);
	unsigned mt2 = mt1;
	for (unsigned i = 2; i < 398; ++i)
		mt2 = (1812433253u * (mt2 ^ (mt2 >> 30u)) + i);
	unsigned k = (mt0 & 0x80000000u) + (mt1 & 0x7FFFFFFFU);
	mt0 = mt2 ^ (k >> 1u);
	if (k & 1)
		mt0 ^= 2567483615u;
	mt0 ^= (mt0 >> 11u);
	mt0 ^= (mt0 << 7u) & 0x9D2C5680u;
	mt0 ^= (mt0 << 15u) & 0xEFC60000u;
	mt0 ^= (mt0 >> 18u);
	return !(mt0 % 10);
}
//获取BDS版本
static PyObject* getBDSVersion(PyObject*, PyObject*) {
	return StrToPyUnicode(Common::getGameVersionString());
}
//指令输出
static PyObject* logout(PyObject*, PyObject* args) {
	const char* msg = "";
	Py_PARSE("s", &msg);
	SymCall("??$_Insert_string@DU?$char_traits@D@std@@_K@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@QEBD_K@Z",
		ostream&, ostream&, const char*, size_t)(cout, msg, strlen(msg));
	Py_RETURN_NONE;
}
//执行指令
static PyObject* runCommand(PyObject*, PyObject* args) {
	const char* cmd = "";
	Py_PARSE("s", &cmd);
	Level::runcmd(cmd);
	//if (global<SPSCQueue> == nullptr)
	//	Py_RETURN_ERROR("Command queue is not initialized");
	//SymCall<bool, SPSCQueue*, const string&>("??$inner_enqueue@$0A@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@?$SPSCQueue@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$0CAA@@@AEAA_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
	//	global<SPSCQueue>, cmd);
	Py_RETURN_NONE;
}
//设置监听
static PyObject* setListener(PyObject*, PyObject* args) {
	const char* event_name = "";
	PyObject* func = nullptr;
	Py_PARSE("sO", &event_name, &func);
	if (!PyFunction_Check(func))
		Py_RETURN_ERROR("Parameter 2 is not callable");
	auto event_code = magic_enum::enum_cast<EventCode>(event_name);
	if (!event_code.has_value())
		Py_RETURN_ERROR_FORMAT("Invalid Listener key words %s", event_name);
	//在全局回调表中查找code
	auto funcs = g_callback_functions.find(event_code.value());
	//如果是第一次设置则订阅监听器
	if (funcs == g_callback_functions.end()) {
		g_callback_functions[event_code.value()];
		EnableEventListener(event_code.value());
	}
	//添加回调函数
	funcs->second.push_back(func);
	Py_RETURN_NONE;
}
//设置指令说明
static PyObject* registerCommand(PyObject*, PyObject* args) {
	const char* cmd = "";
	PyObject* callback = nullptr;
	const char* des = "";
	Py_PARSE("sOs", &cmd, &callback, &des);
	g_commands[cmd] = { des, callback };
	Py_RETURN_NONE;
}
//获取玩家
static PyObject* getPlayerByXuid(PyObject*, PyObject* args) {
	const char* xuid = "";
	Py_PARSE("s", &xuid);
	Player* p = Level::getPlayer(xuid);
	if (p == nullptr)
		Py_RETURN_ERROR("Failed to find player");
	return ToPyEntity(p);
}
//获取玩家列表
static PyObject* getPlayerList(PyObject*, PyObject* args) {
	PyObject* list = PyList_New(0);
	Level::forEachPlayer(
		[list](Player& p)->bool {
			PyList_Append(list, ToPyEntity(&p));
			return true;
		}
	);
	return list;
}
static PyObject* setServerMotd(PyObject*, PyObject* args) {
	const char* name = "";
	Py_PARSE("s", &name);
	if (Global<ServerNetworkHandler> == nullptr)
		Py_RETURN_ERROR("Server did not finish loading");
	SymCall("?allowIncomingConnections@ServerNetworkHandler@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z",
			uintptr_t, ServerNetworkHandler*, const string&, bool)(Global<ServerNetworkHandler>, name, true);
	Py_RETURN_NONE;
}
//根据坐标设置方块
static PyObject* getBlock(PyObject*, PyObject* args) {
	BlockPos bp;
	int did;
	Py_PARSE("iiii", &bp.x, &bp.y, &bp.z, &did);
	BlockSource* bs = Level::getBlockSource(did);
	if (bs == nullptr)
		Py_RETURN_ERROR("Unknown dimension ID");
	Block* b = const_cast<Block*>(&bs->getBlock(bp));

	auto bi = BlockInstance::createBlockInstance(b, bp, did);
	auto ubi = make_unique<BlockInstance>(bi);
	return ToPyBlockInstance(ubi.get());
}
static PyObject* setBlock(PyObject*, PyObject* args) {
	const char* name = "";
	BlockPos bp;
	int did;
	Py_PARSE("siiii", &name, &bp.x, &bp.y, &bp.z, &did);
	BlockSource* bs = Level::getBlockSource(did);
	if (bs == nullptr)
		Py_RETURN_ERROR("Unknown dimension ID");
	Block* b = dAccess<Block*, 0>(SYM((string("?m") + name + "@VanillaBlocks@@3PEBVBlock@@EB").c_str()));
	if (b == nullptr)
		Py_RETURN_ERROR("Unknown Block");
	bs->setBlockSimple(bp, *b);
	Py_RETURN_NONE;
}
//从指定地点获取JSON字符串NBT结构数据
static PyObject* getStructure(PyObject*, PyObject* args) {
	BlockPos pos1, pos2;
	int did;
	bool ignore_entities = true;
	bool ignore_blocks = false;
	Py_PARSE("iiiiiii|bb",
		&pos1.x, &pos1.y, &pos1.z,
		&pos2.x, &pos2.y, &pos2.z, &did,
		&ignore_entities, &ignore_blocks
	);
	auto st = StructureTemplate::fromWorld("name", did, pos1, pos2, ignore_entities, ignore_blocks);
	return StrToPyUnicode(CompoundTagToJson(*st.save()).dump(4));
}
//从JSON字符串NBT结构数据导出结构到指定地点
static PyObject* setStructure(PyObject*, PyObject* args) {
	const char* data = "";
	BlockPos pos;
	int did;
	Mirror mir = None_15;
	Rotation rot = None_14;
	Py_PARSE("siiii|ii",
		&data, &pos.x, &pos.y, &pos.z,
		&did, &mir, &rot
	);
	StructureTemplate::fromTag("name", *ToCompoundTag(CompoundTagToJson(data)))
		.toWorld(did, pos, mir, rot);
	/*for (int x = 0; x != size.x; ++x) {
		for (int y = 0; y != size.y; ++y) {
			for (int z = 0; z != size.z; ++z) {
				BlockPos bp{ x, y, z };
				bs->neighborChanged(bp, bp);
			}
		}
	}*/
	Py_RETURN_NONE;
}
//从指定地点获取二进制NBT结构数据
static PyObject* getStructureBinary(PyObject*, PyObject* args) {
	BlockPos pos1, pos2;
	int did;
	bool ignore_entities = true;
	bool ignore_blocks = false;
	Py_PARSE("iiiiiii|bb",
		&pos1.x, &pos1.y, &pos1.z,
		&pos2.x, &pos2.y, &pos2.z, &did,
		&ignore_entities, &ignore_blocks
	);
	auto st = StructureTemplate::fromWorld("name", did, pos1, pos2, ignore_entities, ignore_blocks);
	BinaryStream binary_stream;
	serialize<CompoundTag>::write(st.save(), &binary_stream);
	return PyBytes_FromStringAndSize(
		binary_stream.getAndReleaseData().c_str(),
		binary_stream.getLength()
	);
}
//从二进制NBT结构数据导出结构到指定地点
static PyObject* setStructureBinary(PyObject*, PyObject* args) {
	const char* data = "";
	Py_ssize_t data_size;
	BlockPos pos;
	int did;
	Mirror mir = None_15;
	Rotation rot = None_14;
	Py_PARSE("y#iiii|ii",
		&data, &data_size, &pos.x, &pos.y, &pos.z,
		&did, &mir, &rot
	);
	ReadOnlyBinaryStream binary_stream = string(data, data_size);
	//printf("bufferlength: %d\n",stream->mBuffer->length());
	auto tag = serialize<CompoundTag>::read(&binary_stream);
	//printf("deserialized.\n");
	if (tag->getTagType() != Tag::Type::Compound)
		Py_RETURN_ERROR("Invalid Tag");
	if (tag->contains("size") || (*tag)["size"]->getTagType() != Tag::Type::List)
		Py_RETURN_ERROR("Invalid Tag");
	StructureTemplate::fromTag("name", *tag)
		.toWorld(did, pos, mir, rot);
	/*for (int x = 0; x != size.x; ++x) {
		for (int y = 0; y != size.y; ++y) {
			for (int z = 0; z != size.z; ++z) {
				BlockPos bp{ x, y, z };
				bs->neighborChanged(bp, bp); // idk what will happen, origin: neighborChanged(bp)
			}
		}
	}*/
	Py_RETURN_NONE;
}
//产生爆炸
static PyObject* explode(PyObject*, PyObject* args) {
	Vec3 pos; int did;
	float power; bool destroy;
	float range; bool fire;
	Py_PARSE("fffifbfb",
		&pos.x, &pos.y, &pos.z, &did,
		&power, &destroy, &range, &fire
	);
	BlockSource* bs = Level::getBlockSource(did);
	if (!bs)
		Py_RETURN_ERROR("Unknown dimension ID");
	Global<Level>->explode(*bs, nullptr, pos, power, fire, destroy, range, true);
	Py_RETURN_NONE;
}
//生成物品
static PyObject* spawnItem(PyObject*, PyObject* args) {
	const char* item_data = "";
	Vec3 pos; int did;
	Py_PARSE("sfffi", &item_data, &pos.x, &pos.y, &pos.z, &did);
	ItemStack item = LoadItemFromString(item_data);
	Global<Level>->getSpawner().spawnItem(pos, did, &item);
	Py_RETURN_NONE;
}
//是否为史莱姆区块
static PyObject* isSlimeChunk(PyObject*, PyObject* args) {
	unsigned x, z;
	Py_PARSE("II", &x, &z);
	if (IsSlimeChunk(x, z))
		Py_RETURN_TRUE;
	else
		Py_RETURN_FALSE;
}
//设置牌子文字
static PyObject* setSignBlockMessage(PyObject*, PyObject* args) {
	const char* name = "";
	BlockPos bp; int did;
	Py_PARSE("siiii", &name, &bp.x, &bp.y, &bp.z, &did);
	if (Global<Level> == nullptr)
		Py_RETURN_ERROR("Level is not set");
	BlockSource* bs = Level::getBlockSource(did);
	if (bs == nullptr)
		Py_RETURN_ERROR("Unknown dimension ID");
	SignBlockActor* sign = static_cast<SignBlockActor*>(bs->getBlockEntity(bp));
	sign->setMessage(name, name);
	sign->setChanged();
	Py_RETURN_NONE;
}
//模块方法列表
static PyMethodDef Methods[]{
	Py_METHOD_NOARGS(getBDSVersion),
	Py_METHOD_VARARGS(logout),
	Py_METHOD_VARARGS(runCommand),
	Py_METHOD_VARARGS(setListener),
	Py_METHOD_VARARGS(registerCommand),
	Py_METHOD_VARARGS(getPlayerByXuid),
	Py_METHOD_NOARGS(getPlayerList),
	Py_METHOD_VARARGS(setServerMotd),
	Py_METHOD_VARARGS(getBlock),
	Py_METHOD_VARARGS(setBlock),
	Py_METHOD_VARARGS(getStructure),
	Py_METHOD_VARARGS(setStructure),
	Py_METHOD_VARARGS(getStructureBinary),
	Py_METHOD_VARARGS(setStructureBinary),
	Py_METHOD_VARARGS(explode),
	Py_METHOD_VARARGS(spawnItem),
	Py_METHOD_VARARGS(isSlimeChunk),
	Py_METHOD_VARARGS(setSignBlockMessage),
	Py_METHOD_END
};
//模块定义
static PyModuleDef Module{
	PyModuleDef_HEAD_INIT,
	"mc",
	"API functions",
	-1,
	Methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};
//模块初始化
extern "C" PyObject * McInit() {
	PyObject* module = PyModule_Create(&Module);
	PyModule_AddObject(module, "Entity", reinterpret_cast<PyObject*>(&PyEntity_Type));
	return module;
}
