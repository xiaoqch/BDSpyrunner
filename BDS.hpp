#pragma once
#include "pch.h"
#include "NBT.hpp"
using namespace std;
struct BlockLegacy {
	string getBlockName() {
		return f(string, this + 128);
	}
	short getBlockItemID() {// IDA Item::beginCreativeGroup(,Block*,) 18~22
		short v3 = f(short, this + 328);
		if (v3 < 0x100) {
			return v3;
		}
		return (short)(255 - v3);
	}
};
struct Block {
	BlockLegacy* getBlockLegacy() {
		return SYMCALL<BlockLegacy*>("?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ", this);
	}
};
struct BlockPos { int x = 0, y = 0, z = 0; };
struct BlockActor {
	Block* getBlock() {
		return f(Block*, this + 16);
	}
	// ȡ����λ��
	BlockPos* getPosition() {// IDA BlockActor::BlockActor 18~20
		return f(BlockPos*, this + 44);
	}
};
struct BlockSource {
	Block* getBlock(BlockPos* bp) {
		return SYMCALL<Block*>("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			this, bp);
	}
	// ��ȡ��������ά��
	int getDimensionId() {	// IDA Dimension::onBlockChanged 42
		return f(int, (f(VA, this + 32) + 208));
	}
};
struct Level {
	VA getScoreBoard() {// IDA Level::removeEntityReferences
		return f(VA, this + 8376);
	}
	struct Actor* fetchEntity(VA id) {
		return SYMCALL<struct Actor*>("?fetchEntity@Level@@QEBAPEAVActor@@UActorUniqueID@@_N@Z",
			this, id, false);
	}
};
struct Vec3 { float x = 0.0f, y = 0.0f, z = 0.0f; };
struct Vec2 { float x = 0.0f, y = 0.0f; };
struct MobEffectInstance { char fill[0x1C]; };
struct Item;
struct ItemStackBase {
	VA vtable;
	VA mItem;
	VA mUserData;
	VA mBlock;
	short mAuxValue;
	char mCount;
	char mValid;
	char unk[4];
	VA mPickupTime;
	char mShowPickUp;
	char unk2[7];
	vector<VA*> mCanPlaceOn;
	VA mCanPlaceOnHash;
	vector<VA*> mCanDestroy;
	VA mCanDestroyHash;
	VA mBlockingTick;
	ItemStackBase* mChargedItem;
	VA uk;

	// ȡ��ƷID,����ֵ,���
	short getId() {
		return SYMCALL<short>("?getId@ItemStackBase@@QEBAFXZ", this);
	}
	short getDamageValue() {
		return SYMCALL<short>("?getDamageValue@ItemStackBase@@QEBAFXZ", this);
	}
	// ȡ��Ʒ����
	string getName() {
		string str;
		SYMCALL<string*>("?getRawNameId@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			this, &str);
		return str;
	}
	// ȡ����������
	int getStackCount() {// IDA ContainerModel::networkUpdateItem
		return f(int, this + 34);
	}
	// �ж��Ƿ������
	bool isNull() {
		return SYMCALL<bool>("?isNull@ItemStackBase@@QEBA_NXZ", this);
	}
	Tag* getNetworkUserData() {
		Tag* ct;
		SYMCALL("?getNetworkUserData@ItemStackBase@@QEBA?AV?$unique_ptr@VCompoundTag@@U?$default_delete@VCompoundTag@@@std@@@std@@XZ",
			this, &ct);
		return ct;
	}
	Tag* save() {
		Tag* t = 0;
		SYMCALL("?save@ItemStackBase@@QEBA?AV?$unique_ptr@VCompoundTag@@U?$default_delete@VCompoundTag@@@std@@@std@@XZ",
			this, &t);
		return t;
	}
	bool isEmptyStack() {
		return f(char, this + 34) == 0;
	}
	ItemStackBase* fromTag(Tag* t) {
		return SYMCALL<ItemStackBase*>("?fromTag@ItemStack@@SA?AV1@AEBVCompoundTag@@@Z",
			this, t);
	}
	bool getFromId(short id, short aux, char count) {
		memcpy(this, SYM("?EMPTY_ITEM@ItemStack@@2V1@B"), 0x90);
		bool ret = SYMCALL<bool>("?_setItem@ItemStackBase@@IEAA_NH@Z", this, id);
		mCount = count;
		mAuxValue = aux;
		mValid = true;
		return ret;
	}
	Item* getItem() {
		return SYMCALL<Item*>("?getItem@ItemStackBase@@QEBAPEBVItem@@XZ", this);
	}
};
struct ItemStack : ItemStackBase {};
struct Container {
	// ��ȡ������������Ʒ
	auto getSlots() {
		vector<ItemStack*> s;
		SYMCALL<VA>("?getSlots@Container@@UEBA?BV?$vector@PEBVItemStack@@V?$allocator@PEBVItemStack@@@std@@@std@@XZ",
			this, &s);
		return s;
	}
	void clearItem(int slot, int num) {
		SYMCALL("?removeItem@Container@@UEAAXHH@Z", this, slot, num);
	}
};
struct Actor {
	// ��ȡ����������Ϣ
	string getNameTag() {
		return SYMCALL<string&>("?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", this);
	}
	// ��ȡ���ﵱǰ����ά��ID
	int getDimensionId() {
		int did;
		SYMCALL<int&>("?getDimensionId@Actor@@UEBA?AV?$AutomaticID@VDimension@@H@@XZ",
			this, &did);
		return did;
	}
	// ��ȡ���ﵱǰ��������
	Vec3* getPos() {
		return SYMCALL<Vec3*>("?getPos@Actor@@UEBAAEBVVec3@@XZ", this);
	}
	// �Ƿ�����
	bool isStand() {// IDA MovePlayerPacket::MovePlayerPacket 30
		return f(bool, this + 448);
	}
	// ȡ����Դ
	BlockSource* getRegion() {
		return f(BlockSource*, this + 3312);
	}
	// ��ȡʵ������
	unsigned getEntityTypeId() {
		return f(unsigned, this + 964);
	}
	// ��ȡ��ѯ��ID
	VA getUniqueID() {
		return SYMCALL<VA>("?getUniqueID@Actor@@QEBAAEBUActorUniqueID@@XZ", this);
	}
	// ��ȡʵ������
	string getEntityTypeName() {
		string en_name;
		SYMCALL<string&>("?EntityTypeToLocString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorType@@W4ActorTypeNamespaceRules@@@Z",
			&en_name, getEntityTypeId());
		return en_name;
	}
	// ��������
	VA updateAttrs() {
		return SYMCALL<VA>("?_sendDirtyActorData@Actor@@QEAAXXZ", this);
	}
	VA getAttribute() {
		return f(VA, this + 1144);
	}
	// ����һ��״̬
	VA addEffect(VA ef) {
		return SYMCALL<VA>("?addEffect@Actor@@QEAAXAEBVMobEffectInstance@@@Z", this, ef);
	}
	// ��ȡ����ֵ
	int getHealth() {
		return SYMCALL<int>("?getHealth@Actor@@QEBAHXZ", this);
	}
	int getMaxHealth() {
		return SYMCALL<int>("?getMaxHealth@Actor@@QEBAHXZ", this);
	}
	void setHealth(int value, int max) {
		VA hattr = ((*(VA(__fastcall**)(Actor*, void*))(*(VA*)this + 1552))(
			this, SYM("?HEALTH@SharedAttributes@@2VAttribute@@B")));
		f(int, hattr + 132) = value;
		f(int, hattr + 128) = max;
		//SYMCALL("?_setDirty@AttributeInstance@@AEAAXXZ", hattr);
	}
	Tag* save() {
		Tag* t = newTag(Compound);
		SYMCALL("?save@Actor@@UEAA_NAEAVCompoundTag@@@Z", this, t);
		return t;
	}
};
struct Mob : Actor {
	// ��ȡ״̬�б�
	auto getEffects() {	// IDA Mob::addAdditionalSaveData 84
		return (vector<MobEffectInstance>*)((VA*)this + 190);
	}
	// ��ȡװ������
	VA getArmor() {		// IDA Mob::addAdditionalSaveData
		return VA(this) + 1400;
	}
	// ��ȡ��ͷ����
	VA getHands() {
		return VA(this) + 1408;		// IDA Mob::readAdditionalSaveData
	}
	// ���浱ǰ����������
	VA saveOffhand(VA hlist) {
		return SYMCALL<VA>("?saveOffhand@Mob@@IEBA?AV?$unique_ptr@VListTag@@U?$default_delete@VListTag@@@std@@@std@@XZ",
			this, hlist);
	}
	// ��ȡ��ͼ��Ϣ
	VA getLevel() {// IDA Mob::die 143
		return f(VA, this + 856);
	}
};
struct Player : Mob {
	string getUuid() {// IDA ServerNetworkHandler::_createNewPlayer 217
		string p;
		SYMCALL<string&>("?asString@UUID@mce@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			this + 2824, &p);
		return p;
	}
	// �������ݰ�
	void sendPacket(VA pkt) {
		return SYMCALL<void>("?sendNetworkPacket@ServerPlayer@@UEBAXAEAVPacket@@@Z",
			this, pkt);
	}
	// ���ݵ�ͼ��Ϣ��ȡ���xuid
	string& getXuid() {
		return SYMCALL<string&>("?getPlayerXUID@Level@@QEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVUUID@mce@@@Z",
			getLevel(), this + 2824);
	}
	// ��������������
	void setName(string name) {
		SYMCALL("?setName@Player@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
			this, name);
	}
	// ��ȡ�����ʶ��
	VA getNetId() {
		return (VA)this + 2536;// IDA ServerPlayer::setPermissions 34
	}
	// ��ȡ����
	Container* getContainer() {
		return (Container*)f(VA, f(VA, this + 3048) + 176);
	}
	VA getContainerManager() {
		return (VA)this + 3040;		// IDA Player::setContainerManager 18
	}
	// ��ȡĩӰ��
	Container* getEnderChestContainer() {
		return SYMCALL<Container*>("?getEnderChestContainer@Player@@QEAAPEAVEnderChestContainer@@XZ", this);
	}
	// ����һ��װ��
	VA setArmor(int i, ItemStack* item) {
		return SYMCALL<VA>("?setArmor@ServerPlayer@@UEAAXW4ArmorSlot@@AEBVItemStack@@@Z", this, i, item);
	}
	// ���ø���
	VA setOffhandSlot(ItemStack* item) {
		return SYMCALL<VA>("?setOffhandSlot@Player@@UEAAXAEBVItemStack@@@Z", this, item);
	}
	// ����һ����Ʒ
	void addItem(ItemStackBase* item) {
		SYMCALL<VA>("?addItem@@YAXAEAVPlayer@@AEAVItemStack@@@Z", this, item);
	}
	// ��ȡ��ǰѡ�еĿ�λ��
	int getSelectdItemSlot() {// IDA Player::getSelectedItem 12
		return f(unsigned, f(VA, this + 3048) + 16);
	}
	// ��ȡ��ǰ��Ʒ
	ItemStack* getSelectedItem() {
		return SYMCALL<ItemStack*>("?getSelectedItem@Player@@QEBAAEBVItemStack@@XZ", this);
	}
	// ��ȡ������Ʒ
	ItemStack* getInventoryItem(int slot) {
		return SYMCALL<ItemStack*>("?getItem@FillingContainer@@UEBAAEBVItemStack@@H@Z", *(__int64**)(*((__int64*)this + 0x17D) + 0xB0), slot);
	}
	// ��ȡ��Ϸʱ����Ȩ��
	char getPermission() {// IDA ServerPlayer::setPermissions 17
		return *f(char*, this + 2216);
	}
	// ������Ϸʱ����Ȩ��
	void setPermission(char m) {
		SYMCALL("?setPermissions@ServerPlayer@@UEAAXW4CommandPermissionLevel@@@Z",
			this, m);
	}
	// ��ȡ��Ϸʱ����Ȩ��
	char getPermissionLevel() {// IDA Abilities::setPlayerPermissions ?
		return f(char, f(char*, this + 2192) + 1);
	}
	// ������Ϸʱ����Ȩ��
	void setPermissionLevel(char m) {
		SYMCALL("?setPlayerPermissions@Abilities@@QEAAXW4PlayerPermissionLevel@@@Z",
			this + 2192, m);
	}
	void sendInventroy() {
		SYMCALL("?sendInventory@ServerPlayer@@UEAAX_N@Z",
			this, true);
	}
	void teleport(Vec3 target, int dim) {
		SYMCALL("?teleport@TeleportCommand@@SAXAEAVActor@@VVec3@@PEAV3@V?$AutomaticID@VDimension@@H@@VRelativeFloat@@4HAEBUActorUniqueID@@@Z",
			this, target, 0, dim, 0, 0, 0, SYM("?INVALID_ID@ActorUniqueID@@2U1@B"));
	}
};
struct PlayerScore {
	VA getscore() {
		return f(VA, this + 4);
	}
};
struct ScoreInfo {
	//scoreboardcmd list; objective::objective; scoreboard getscores
	//int scores    +12 this[12]
	// string displayname  +96
	//string name +64
	int getCount() {
		return f(int, this + 12);
	}
};
struct ScoreboardId {
	int id;
	VA null;
};
struct ScorePacketInfo {
	ScoreboardId sid;
	string obj_name = "name";
	unsigned score;
	enum Type : char { Invalid = 0, Player = 1, Actor = 2, Fake = 3 };
	Type type = Fake;
	VA pid;
	VA aid;
	string fake_name;

	ScorePacketInfo(ScoreboardId* s, unsigned num, const string& fake) :
		sid(*s), score(num), fake_name(fake) {}

};
struct Objective {
	//��ȡ�Ʒְ�����
	auto getScoreName() {
		return f(string, this + 64);
	}
	//��ȡ�Ʒְ�չʾ����
	auto getScoreDisplayName() {
		return f(string, this + 96);
	}
	auto createScoreboardId(Player* player) {
		return SYMCALL<ScoreboardId*>("?createScoreboardId@ServerScoreboard@@UEAAAEBUScoreboardId@@AEBVPlayer@@@Z", this, player);
	}
	ScoreInfo* getPlayerScore(ScoreboardId* a2) {
		char a1[12];
		return SYMCALL<ScoreInfo*>("?getPlayerScore@Objective@@QEBA?AUScoreInfo@@AEBUScoreboardId@@@Z",
			this, a1, a2);
	}
};
struct Scoreboard {
	auto getObjective(string str) {
		return SYMCALL<Objective*>("?getObjective@Scoreboard@@QEBAPEAVObjective@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z", this, &str);
	}
	auto getScoreboardId(const string& str) {
		return SYMCALL<ScoreboardId*>("?getScoreboardId@Scoreboard@@QEBAAEBUScoreboardId@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
			this, &str);
	}
	vector<Objective*> getObjectives() {
		vector<Objective*> s;
		SYMCALL("?getObjectives@Scoreboard@@QEBA?AV?$vector@PEBVObjective@@V?$allocator@PEBVObjective@@@std@@@std@@XZ",
			this, &s);
		return s;
	}
	auto getDisplayInfoFiltered(string* str) {
		return SYMCALL<vector<PlayerScore>*>("?getDisplayInfoFiltered@Scoreboard@@QEBA?AV?$vector@UPlayerScore@@V?$allocator@UPlayerScore@@@std@@@std@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z", this, str);
	}
	auto getTrackedIds() {
		return SYMCALL<vector<ScoreboardId>*>("?getTrackedIds@Scoreboard@@QEBA?AV?$vector@UScoreboardId@@V?$allocator@UScoreboardId@@@std@@@std@@XZ", this);
	}
	auto getScoreboardId(Player* a2) {
		return SYMCALL<ScoreboardId*>("?getScoreboardId@Scoreboard@@QEBAAEBUScoreboardId@@AEBVActor@@@Z", this, a2);
	}
	//������ҷ���
	int modifyPlayerScore(ScoreboardId* a3, Objective* a4, int count, int mode) {
		bool a2 = true;
		return SYMCALL<int>("?modifyPlayerScore@Scoreboard@@QEAAHAEA_NAEBUScoreboardId@@AEAVObjective@@HW4PlayerScoreSetFunction@@@Z",
			this, &a2, a3, a4, count, mode);
	}
	auto createScoreBoardId(const string& s) {
		return SYMCALL<ScoreboardId*>("?createScoreboardId@ServerScoreboard@@UEAAAEBUScoreboardId@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
			this, &s);
	}
	auto createScoreBoardId(Player* player) {
		return SYMCALL<ScoreboardId*>("?createScoreboardId@ServerScoreboard@@UEAAAEBUScoreboardId@@AEBVPlayer@@@Z", this, player);
	}
};