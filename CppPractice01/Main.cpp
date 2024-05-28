#include"Employee.h"
#include <vector>
#include <memory>

Employee Input();
void Output(Employee employee);
int	TotalPay(Employee employee);

int main()
{
    std::vector<Employee> employees;
	int menu;

	bool loop = true;
	while (loop)
	{
		std::cout << "메뉴를 선택하십시오\n 1.입력\n 2.출력\n 3.종료\n";
		cin >> menu;

		switch (menu)
		{
			// 입력
		case 1:
			employees.push_back(Input());
			break;

			// 출력
		case 2:
			for (vector<Employee>::iterator iter = employees.begin(); iter != employees.end(); iter++)
			{
				Output(*iter);
			}
			break;

			// 종료
		case 3:
			loop = false;
			break;

		default:
			cout << "오류! 다시 선택해주십시오!" << endl;
		}
	}
}

Employee Input()
{
	Employee employee;
	string name;
	int position;
	int salaryType;
	int workTime;
	int	year;
	int	grade;

	cout << "입력을 선택하셨습니다." << endl;

	// 이름
	cout << "이름을 입력해 주십시오: ";
	cin >> name;
	employee.SetName(name);
	cout << "이름 입력이 완료되었습니다." << endl << endl;

	// 직급
	cout << "직급을 선택해 주십시오. \n" << "1.사원 2.대리 3.과장 4.부장 5.이사" << endl;
	cin >> position;
	switch (position)
	{
	case 1:
		employee.SetPosition(Position::Staff);
		break;
	case 2:
		employee.SetPosition(Position::Assistant);
		break;
	case 3:
		employee.SetPosition(Position::General);
		break;
	case 4:
		employee.SetPosition(Position::Director);
		break;
	case 5:
		employee.SetPosition(Position::Excutive);
		break;
	default:
		cout << "오류! 다시 선택해주십시오!" << endl;
	}
	cout << "직급 입력이 완료되었습니다." << endl << endl;

	// 급여산출방식
	cout << "급여산출방식을 선택해 주십시오. \n" << "1.시급제 2.월급제 3.연봉제" << endl;
	cin >> salaryType;
	switch (salaryType)
	{
	case 1:
		employee.SetSalaryType(SalaryType::Hourly);
		break;
	case 2:
		employee.SetSalaryType(SalaryType::Monthly);
		break;
	case 3:
		employee.SetSalaryType(SalaryType::Yearly);
		break;
	default:
		cout << "오류! 다시 선택해주십시오!" << endl;
	}
	cout << "급여산출방식 입력이 완료되었습니다." << endl << endl;

	// 근무시간(시급제), 근속연수(월급제), 능력등급(연봉제)
	switch (salaryType)
	{
	case 1:
		cout << "이번달 근무 시간을 입력해주십시오: ";
		cin >> workTime;
		employee.SetWorkTime(workTime);
		cout << "근무 시간 입력이 완료되었습니다." << endl << endl;
		break;
	case 2:
		cout << "근속연수를 입력해주십시오: ";
		cin >> year;
		employee.SetYear(year);
		cout << "근속연수 입력이 완료되었습니다." << endl << endl;
		break;
	case 3:
		cout << "능력등급을 입력해주십시오: ";
		cin >> grade;
		employee.SetGrade(grade);
		cout << "능력등급 입력이 완료되었습니다." << endl << endl;
		break;
	default:
		cout << "오류! 다시 선택해주십시오!" << endl;
	}

	return employee;
}

void Output(Employee employee)
{
	// 이름
	cout << "이름: " << employee.GetName() << "  //  ";

	// 직급
	switch (employee.GetPosition())
	{		
	case Position::Staff:
		cout << "직급: 사원" << "  //  ";
		break;
	case Position::Assistant:
		cout << "직급: 대리" << "  //  ";
		break;
	case Position::General:
		cout << "직급: 과장" << "  //  ";
		break;
	case Position::Director:
		cout << "직급: 부장" << "  //  ";
		break;
	case Position::Excutive:
		cout << "직급: 이사" << endl;
		break;
	default:
		//cout << "전산 오류!" << endl;
		break;
	}

	// 급여 산출 방식
	switch (employee.GetSalaryType())
	{
	case SalaryType::Hourly:
		cout << "급여산출방식: 시급제" << "  //  ";
		break;
	case SalaryType::Monthly:
		cout << "급여산출방식: 월급제" << "  //  ";
		break;
	case SalaryType::Yearly:
		cout << "급여산출방식: 시급제" << endl;
		break;
	default:
		//cout << "전산 오류!" << endl;
		break;
	}

	// 비고
	switch (employee.GetSalaryType())
	{
	case SalaryType::Hourly:
		cout << "비고: 월" << employee.GetWorkTime() << "시간 근무" << "  //  ";
		break;
	case SalaryType::Monthly:
		cout << "비고: " << employee.GetYear() << "년차" << "  //  ";
		break;
	case SalaryType::Yearly:
		cout << "비고: 능력 " << employee.GetGrade() << "등급" << endl;
		break;
	default:
		//cout << "전산 오류!" << endl;
		break;
	}

	// 월급 계산 결과
	cout << employee.GetName() << "님의 이번 달 월급은 " << TotalPay(employee) << "만원 입니다." << endl;

	cout << endl;
}

int	TotalPay(Employee employee)
{
	int result = 0;

	switch (employee.GetSalaryType())
	{
	// 시급제
	case SalaryType::Hourly:
		switch (employee.GetPosition())
		{
		case Position::Staff:
			result = employee.GetWorkTime() * 1;
			break;
		case Position::Assistant:
			result = employee.GetWorkTime() * 2;
			break;
		case Position::General:
			result = employee.GetWorkTime() * 4;
			break;
		case Position::Director:
			result = employee.GetWorkTime() * 6;
			break;
		case Position::Excutive:
			result = employee.GetWorkTime() * 8;
			break;
		default:
			break;
		}

	// 월급제
	case SalaryType::Monthly:
		switch (employee.GetPosition())
		{
		case Position::Staff:
			result = 200 + 20 * 0 + employee.GetYear() * 5;
			break;
		case Position::Assistant:
			result = 200 + 20 * 1 + employee.GetYear() * 5;
			break;
		case Position::General:
			result = 200 + 20 * 2 + employee.GetYear() * 5;
			break;
		case Position::Director:
			result = 200 + 20 * 3 + employee.GetYear() * 5;
			break;
		case Position::Excutive:
			result = 200 + 20 * 4 + employee.GetYear() * 5;
			break;
		default:
			break;
		}

	// 연봉제
	case SalaryType::Yearly:
		switch (employee.GetPosition())
		{
		case Position::Staff:
			result = (2000 + 1000 * 0 + employee.GetGrade() * 500) / 12;
			break;
		case Position::Assistant:
			result = (2000 + 1000 * 1 + employee.GetGrade() * 500) / 12;
			break;
		case Position::General:
			result = (2000 + 1000 * 2 + employee.GetGrade() * 500) / 12;
			break;
		case Position::Director:
			result = (2000 + 1000 * 3 + employee.GetGrade() * 500) / 12;
			break;
		case Position::Excutive:
			result = (2000 + 1000 * 4 + employee.GetGrade() * 500) / 12;
			break;
		default:
			break;
		}

	default:
		//cout << "전산 오류!" << endl;
		break;
	}

	return result;
}
