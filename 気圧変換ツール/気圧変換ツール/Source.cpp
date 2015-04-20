#include<Windows.h>
#include<iostream>
#include"mystring.h"
#include<array>
#include<cstdlib>
#include<limits.h>//in gcc
#include<errno.h>//in gcc
#ifdef _UNICODE
#define CF_T_TEXT CF_UNICODETEXT
#else
#define CF_T_TEXT CF_TEXT
#endif
typedef enum pressure_unit{
	UNKNOWN = 0,
	MMHG,
	HPA,
	ATM,
	BAR
} pressure_unit_t;
typedef struct{
	double pressure;
	pressure_unit_t in_unit;
	pressure_unit_t out_unit;
}input_pressure_data_t;
template <typename T, typename ...Args>
inline std::array<T, sizeof...(Args)> make_array(Args &&...args) {
	return std::array<T, sizeof...(Args)>{ std::forward<Args>(args)... };
}
namespace pressure_units{
	static const auto units = make_array<std::string>("mmHg", "hPa", "atm", "bar");
	class basic_pressure_t
	{
	public:
		basic_pressure_t(double hPa){
			this->hPa = hPa;
		}
		basic_pressure_t(double in_pressure, const pressure_unit_t unit){
			hPa = 0;//一度hPaに単位を変換する
			switch (unit)
			{
			case MMHG:
				hPa = in_pressure * 1013.25 / 760;
				break;
			case HPA:
				hPa = in_pressure;
				break;
			case ATM:
				hPa = in_pressure * 1013.25;
				break;
			case BAR:
				hPa = in_pressure * 1000;
				break;
			default:
				throw "unknown units";
				break;
			}
			//in_pressureがhPa以外なら直接代入(計算誤差を減らす)、違ったら変換
			mmHg = (MMHG != unit) ? hPa * 760 / 1013.25 : in_pressure;
			atm = (ATM != unit) ? hPa / 1013.25 : in_pressure;
			bar = (BAR != unit) ? hPa / 1000 : in_pressure;
		}
		std::string to_string(const pressure_unit_t unit) const{
			std::string re = "";
			switch (unit)
			{
			case MMHG:
				re += std::to_string(mmHg);
				break;
			case HPA:
				re += std::to_string(hPa);
				break;
			case ATM:
				re += std::to_string(atm);
				break;
			case BAR:
				re += std::to_string(bar);
				break;
			default:
				throw "unknown units";
				break;
			}
			re += (UNKNOWN == unit) ? "" : units.at(unit - 1);//単位をくっつける
			return re;
		}
	private:
		double hPa, mmHg, atm, bar;
	};
}
pressure_unit_t to_pressure_unit(const std::string& in_str, size_t* _Idx = nullptr){
	using namespace pressure_units;
	if (0 == in_str.length()) return UNKNOWN;
	std::string::size_type place = 0, i = 0;
	for (auto& u : units){
		place = in_str.find(u);
		if (0 == place) break;
		++i;
	}
	if (0 != place) return UNKNOWN;
	if (nullptr != _Idx) *_Idx = units.at(i).length();//in_str中のkey(units[i])のすぐ後の要素番号を引数経由で返す
	return static_cast<pressure_unit_t>(i + 1);
}
template <typename T_>
pressure_unit_t ask_unit(T_ pressure){
	using namespace std;
	string in_unit_str;
	in_unit_str.reserve(10);
	pressure_unit_t re;
	do{
		cout << pressure << "の単位を入力してください" << endl;
		for (auto& i : pressure_units::units) cout << i << ", ";
		cout << endl;
		getline(cin, in_unit_str);
		re = to_pressure_unit(in_unit_str);
	} while (UNKNOWN == re);
	return re;
}
void split_into_pressure_data(input_pressure_data_t& data, const std::string& in_str){
	std::string::size_type in_unit_str_at = 0, out_unit_str_at = 0;
	data.pressure = stod(in_str, &in_unit_str_at);//doubleに変換
	const pressure_unit_t in_unit_temp = to_pressure_unit(in_str.substr(in_unit_str_at), &out_unit_str_at);
	data.in_unit = (UNKNOWN == in_unit_temp) ? ask_unit(data.pressure) : in_unit_temp;
	//in_unitでask_unitを呼び出しているならout_unitでも呼ぶ必要がある
	const pressure_unit_t out_unit_temp = (UNKNOWN == in_unit_temp) ? ask_unit("変換後") : to_pressure_unit(in_str.substr(in_unit_str_at + out_unit_str_at + 2));
	data.out_unit = (UNKNOWN == out_unit_temp) ? ask_unit("変換後") : out_unit_temp;
}
void common_message(void){
	puts("気圧変換ツール\n");
}
void input(input_pressure_data_t& data){
	using namespace std;
	common_message();
	cout << "気圧を入力してください" << endl;
	cout << "[数値][単位]->[変換先単位]" << endl;
	cout << "単位:";
	for (auto& i : pressure_units::units) cout << i << ", ";
	cout << endl;
	cout << "ex.) 760mmHg->atm" << endl;
	string in_str;
	in_str.reserve(15);
	getline(cin, in_str);
	split_into_pressure_data(data, in_str);
}
std::string convert(const input_pressure_data_t& data){
	pressure_units::basic_pressure_t in(data.pressure, data.in_unit);
	return in.to_string(data.out_unit);//単位を変換しつつ文字列に変換しつつ・・・。
}
// *********************************************************
// クリップボードへテキストをコピー
// 戻り値 : 成功 true, 失敗 false
// *********************************************************
bool LboxCopyClipboard(const std::tstring& szData){
	HGLOBAL hGlobal;
	LPTSTR pMem;

	hGlobal = GlobalAlloc(GHND, szData.length() + 128);
	if (nullptr == hGlobal) {
		return false;
	}
	pMem = static_cast<LPTSTR>(GlobalLock(hGlobal));
	if (nullptr == pMem) {
		GlobalFree(hGlobal);
		return false;
	}
	lstrcpy(pMem, szData.c_str());
	GlobalUnlock(hGlobal);
	OpenClipboard(nullptr);
	EmptyClipboard();
	SetClipboardData(CF_T_TEXT, hGlobal);
	CloseClipboard();

	return true;
}

int main(void){
	input_pressure_data_t data;
	input(data);//入力を受ける
	const std::string o_str = convert(data);
	std::tstring to_clipboard;
	StrToTstr(o_str, to_clipboard);
	std::cout << "クリップボードへの出力に" << ((LboxCopyClipboard(to_clipboard)) ? "成功しました" : "失敗しました") << std::endl;
	std::cout << o_str << std::endl;//変換して出力
	return 0;
}
