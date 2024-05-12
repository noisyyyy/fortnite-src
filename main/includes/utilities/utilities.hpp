#pragma once
#include <cstdint>

enum bone : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot2 = 73,
	HumanLFoot = 86,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot2 = 82,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanLHand = 11,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRHand = 40,
	HumanRPalm = 58,
	HumanNeck = 66,
	HumanHead = 109,
	HumanLowerHead = 106,

	HumanChest = 65
};

enum offset {
	uworld = 0x11770D88, // sigma
	game_instance = 0x1D0, // sigma
	game_state = 0x158, // sigma
	persistent_level = 0x30, // sigma
	local_player = 0x38, // sigma
	player_controller = 0x30, // sigma
	acknowledged_pawn = 0x338, // sigma
	skeletal_mesh = 0x318,  // sigma
	player_state = 0x2B0, // sigma
	root_component = 0x198, // sigma
	relative_location = 0x120, // sigma
	relative_rotation = 0x138, // sigma
	team_index = 0x10f1, // sigma
	player_array = 0x2A8, // sigma
	pawn_private = 0x308, // sigma
	current_weapon = 0xA20, // sigma
	weapon_data = 0x4D0, // sigma
	velocity = 0x168, // sigma
	tier = 0x11B,
	is_cached = 0x648,
	bone_array = 0x598, // sigma
	component_to_world = 0x1C0, // sigma
	location_under_reticle = 0x2560,
	fLastSubmitTime = 0x368,
	fLastRenderTimeOnScreen = 0x370,
};


class Pointers {
public:
	uintptr_t
		uworld,
		game_instance,
		game_state,
		local_player,
		acknowledged_pawn,
		player_state,
		player_controller,
		root_component,
		skeletal_mesh,
		persistent_level,
		world_settings,
		WorldGravityZ,
		player_array,
		levels,

		player_array_size,
		current_weapon,
		current_vehicle;
	int
		team_index;
	FVector
		relative_location;
}; static Pointers* pointer = new Pointers();

namespace camera
{
	FVector location, rotation;
	float fov;
}






struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};
std::string LocalPlayerWeapon;


struct Cheat_info
{

	std::string Cheat_name;
	std::string Cheat_Version;
	int branding_type = 0;
	bool star = false;
	bool orbit = false;
	bool River = true;


};

struct camera_position_s {
	FVector location{};
	FVector rotation{};
	float fov{};
};
inline camera_position_s camera_postion{};

Cheat_info Cheat_shi;


WeaponInformation WeaponInfo;


float target_dist = FLT_MAX;
uintptr_t  target_entity = NULL;
uintptr_t  desync_target_entity = NULL;
namespace utilities {
	class c_utilities {
	public:

		bool debug = 0;

	

		auto InScreen(FVector2d screen_position) -> bool {

			if (screen_position.x > 0 && screen_position.x < globals->width && screen_position.y > 0 && screen_position.y < globals->height)
				return true;
			else
				return false;

		}

		auto IsShootable(FVector lur, FVector wl) -> bool {

			if (lur.x >= wl.x - 20 && lur.x <= wl.x + 20 && lur.y >= wl.y - 20 && lur.y <= wl.y + 20 && lur.z >= wl.z - 30 && lur.z <= wl.z + 30)
				return true;
			else
				return false;

		}

		auto IsVisible(uintptr_t skeletal_mesh) -> bool {
			auto last_submit = read<float>(skeletal_mesh + 0x2E8);
			auto last_render = read<float>(skeletal_mesh + 0x2F0);
			const float fVisionTick = 0.06f;
			bool visible = last_render + fVisionTick >= last_submit;
			return visible;
		}

	

		static auto GetBoneLocation(uintptr_t skeletal_mesh, int bone_index) -> FVector {

			uintptr_t bone_array = read<uintptr_t>(skeletal_mesh + offset::bone_array);
			if (bone_array == NULL) bone_array = read<uintptr_t>(skeletal_mesh + offset::bone_array + 0x10);
			ftransform bone = read<ftransform>(bone_array + (bone_index * 0x60));
			ftransform component_to_world = read<ftransform>(skeletal_mesh + offset::component_to_world);
			D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
			return FVector(matrix._41, matrix._42, matrix._43);
		}


		struct FMinimalViewInfo
		{
			FVector Location, Rotation;
			float FOV;
		};




		struct CamewaDescwipsion
		{
			Vector3 Location;
			Vector3 Rotation;
			float FieldOfView;
		};





		static auto UpdateCamera() -> void
		{
			auto location_pointer = read<uintptr_t>(pointer->uworld + 0x110);
			auto rotation_pointer = read<uintptr_t>(pointer->uworld + 0x120);

			struct FNRotation
			{
				double a; //0x0000
				char pad_0008[24]; //0x0008
				double b; //0x0020
				char pad_0028[424]; //0x0028
				double c; //0x01D0
			}tpmrotation;

			tpmrotation.a = read<double>(rotation_pointer);
			tpmrotation.b = read<double>(rotation_pointer + 0x20);
			tpmrotation.c = read<double>(rotation_pointer + 0x1d0);

			camera::rotation.x = asin(tpmrotation.c) * (180.0 / M_PI);
			camera::rotation.y = ((atan2(tpmrotation.a * -1, tpmrotation.b) * (180.0 / M_PI)) * -1) * -1;
			camera::rotation.z = 0;
			camera::location = read<FVector>(location_pointer);
			camera::fov = read<float>(pointer->player_controller + 0x394) * 90.f;
		}


		//static auto UpdateCamera() -> void
		//{
		//	auto location_pointer = read<uintptr_t>(pointer->uworld + 0x110);
		//	auto rotation_pointer = read<uintptr_t>(pointer->uworld + 0x120);

		//	struct FNRotation
		//	{
		//		double a; //0x0000
		//		char pad_0008[24]; //0x0008
		//		double b; //0x0020
		//		char pad_0028[424]; //0x0028
		//		double c; //0x01D0
		//	}tpmrotation;

		//	tpmrotation.a = read<double>(rotation_pointer);
		//	tpmrotation.b = read<double>(rotation_pointer + 0x20);
		//	tpmrotation.c = read<double>(rotation_pointer + 0x1d0);

		//	camera::rotation.x = asin(tpmrotation.c) * (180.0 / M_PI);
		//	camera::rotation.y = ((atan2(tpmrotation.a * -1, tpmrotation.b) * (180.0 / M_PI)) * -1) * -1;
		//	camera::rotation.z = 0;
		//	camera::location = read<FVector>(location_pointer);
		//	camera::fov = read<float>(pointer->player_controller + 0x394) * 90.f;

		//	std::cout << location_pointer << std::endl;
		//	std::cout << rotation_pointer << std::endl;
		//}

		static auto WorldToScreen(FVector worldlocation) -> FVector2d {


			D3DMATRIX tempMatrix = Matrix(camera::rotation);

			FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
			FVector vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
			FVector vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

			FVector vDelta = worldlocation - camera::location;
			FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

			if (vTransformed.z < 1.f)
				vTransformed.z = 1.f;
			return FVector2d((globals->width / 2.0f) + vTransformed.x * (((globals->width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z, (globals->height / 2.0f) - vTransformed.y * (((globals->width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z);

		}
		int screen_width1;
		int screen_heigh1t;

		auto cursor_to(float x, float y) -> void {
			FVector center(globals->width / 2, globals->height / 2, 0);
			FVector target(0, 0, 0);
			
			if (x != 0) {
				if (x > center.x) {
					target.x = -(center.x - x);
					target.x /= (globals->smooth);
					if (target.x + center.x > center.x * 2)
						target.x = 0;
				}

				if (x < center.x) {
					target.x = x - center.x;
					target.x /= (globals->smooth);
					if (target.x + center.x < 0)
						target.x = 0;
				}
			}
			if (y != 0) {
				if (y > center.y) {
					target.y = -(center.y - y);
					target.y /= (globals->smooth);
					if (target.y + center.y > center.y * 2)
						target.y = 0;
				}

				if (y < center.y) {
					target.y = y - center.y;
					target.y /= (globals->smooth);
					if (target.y + center.y < 0)
						target.y = 0;
				}
			}

			const float snapThreshold = 1.0f;
			if (std::abs(target.x) < snapThreshold) {
				target.x = 0;
			}
			if (std::abs(target.y) < snapThreshold) {
				target.y = 0;
			}

			Inject->set_cursor_position(target.x, target.y);
	/*		memory_helper::Write<FVector>(pointer->player_controller + 0x518, Angles);
			memory_helper::Write<FVector>(pointer->player_controller + 0x960, Angles);*/


		}

		auto cursor_to2(float x, float y) -> void {
			FVector center(globals->width / 2, globals->height / 2, 0);
			FVector target(0, 0, 0);

			target.x = (x > center.x) ? -(center.x - x) : x - center.x;
			target.x /= globals->smooth;
			target.x = (target.x + center.x > center.x * 2 || target.x + center.x < 0) ? 0 : target.x;

			target.y = (y > center.y) ? -(center.y - y) : y - center.y;
			target.y /= globals->smooth;
			target.y = (target.y + center.y > center.y * 2 || target.y + center.y < 0) ? 0 : target.y;

			FVector Angles(-target.y / globals->smooth, target.x / globals->smooth, 0);


			const float snapThreshold = 1.0f;
			if (std::abs(target.x) < snapThreshold) {
				target.x = 0;
			}
			if (std::abs(target.y) < snapThreshold) {
				target.y = 0;
			}

			
			//write<FVector>(pointer->player_controller + 0x520, Angles);
			//write<FVector>(pointer->player_controller + 0x528, Angles);


		}

		FVector calc_angle(FVector LocalPos, FVector WorldPos) {
			FVector RelativePos = WorldPos - LocalPos;
			float yaw = atan2(RelativePos.y, RelativePos.x) * 180.0f / M_PI;
			float pitch = -((acos(RelativePos.z / LocalPos.Distance(WorldPos)) * 180.0f / M_PI) - 90.0f);
			return FVector(pitch, yaw, 0);
		}

		static void normalize(FVector& in)
		{
			while (in.x > 180.0f)
				in.x -= 360.0f;

			while (in.x < -180.0f)
				in.x += 360.0f;

			while (in.y > 180.0f)
				in.y -= 360.0f;

			while (in.y < -180.0f)
				in.y += 360.0f;

			in.z = 0;
		}

		__forceinline double Clamp(double value, double min, double max)
		{
			if (value < min) {
				return min;
			}
			else if (value > max) {
				return max;
			}
			else {
				return value;
			}
		}

		/*inline void aimbot_event(FVector target) {
			FVector calc = calc_angle(camera::location, target);
			normalize(calc);

			FVector current_rot = camera::rotation;
			normalize(current_rot);

			FVector delta = calc - current_rot;
			normalize(delta);

			delta.x = delta.x / globals->smooth;
			delta.y = delta.y / globals->smooth;



			FVector input = FVector(Clamp(delta.x, -0.098f, 0.098f), Clamp(delta.y, -0.098f, 0.098f), 0);

			driver.write<FVector>((uint64_t)pointer->player_controller + 0x520, input);
			driver.write<FVector>((uint64_t)pointer->player_controller + 0x968, input);
		}*/


		std::string DecryptName(__int64 PlayerState)
		{
			int pNameLength; // rsi
			_WORD* pNameBufferPointer;
			int i;      // ecx
			char v25; // al
			int v26;  // er8
			int v29;  // eax

			char16_t* pNameBuffer;

			uintptr_t pNameStructure = read<uintptr_t>(PlayerState + 0xAF0);
			pNameLength = read<int>(pNameStructure + 0x10);

			if (pNameLength <= 0)
				return "AI/NONE";

			pNameBuffer = new char16_t[pNameLength];
			uintptr_t pNameEncryptedBuffer = read<uintptr_t>(pNameStructure + 0x8);

			mem::read_physical(reinterpret_cast<void*>(pNameEncryptedBuffer), reinterpret_cast<uint8_t*>(pNameBuffer), pNameLength);
			v25 = pNameLength - 1;
			v26 = 0;
			pNameBufferPointer = (_WORD*)pNameBuffer;

			for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7) {
				v29 = pNameLength - 1;
				if (!(_DWORD)pNameLength)
					v29 = 0;

				if (v26 >= v29)
					break;

				i += 3;
				++v26;
			}

			std::u16string temp_wstring(pNameBuffer);
			delete[] pNameBuffer;
			return std::string(temp_wstring.begin(), temp_wstring.end());
		}

		static float powf_(float _X, float _Y) {
			return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
		}
		static float sqrtf_(float _X) {
			return (_mm_cvtss_f32(_mm_sqrt_ps(_mm_set_ss(_X))));
		}
		static double GetCrossDistance(double x1, double y1, double x2, double y2) {
			return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
		}

	};
} static utilities::c_utilities* Utilities = new utilities::c_utilities();