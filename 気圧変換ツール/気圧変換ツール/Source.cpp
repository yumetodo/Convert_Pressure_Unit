#include<iostream>
#include<string>
#include<array>
#include<typeinfo>
#include<cstdio>
#include<cstdlib>
#include<limits.h>//in gcc
#include<errno.h>//in gcc
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
			hPa = 0;
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
			re += (UNKNOWN == unit) ? "" : units.at(unit - 1);
			return re;
		}
	private:
		double hPa, mmHg, atm, bar;
	};
}
pressure_unit_t to_pressure_unit(const std::string& in_str, size_t* _Idx = nullptr){
	using namespace pressure_units;
	if (0 == in_str.length()) return UNKNOWN;
	//static const auto units = make_array<std::string>("mmHg", "hPa", "atm", "bar");
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
		cout << "mmHg, hPa, atm, bar" << endl;
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
	printf("気圧変換ツール\n\n");
}
void input(input_pressure_data_t& data){
	using namespace std;
	common_message();
	cout << "気圧を入力してください" << endl;
	string in_str;
	in_str.reserve(15);
	getline(cin, in_str);
	split_into_pressure_data(data, in_str);
}
std::string convert(const input_pressure_data_t& data){
	using namespace pressure_units;
	basic_pressure_t in(data.pressure, data.in_unit);
	return in.to_string(data.out_unit);
}
int main(void){
	input_pressure_data_t data;
	input(data);
	std::cout << convert(data) << std::endl;
	return 0;
}
