#include<stdio.h>
#include<string.h>

//declear the functions
void addEmployee();
void searchEmployee();
void deleteEmployee();
void getSalaryReport();
void displayAllEmployees();
int getEmployeeCount();
void updateEmployee();

//HR system main menu
int main(){
	int option;
	
	printf("\nAdd Employee ---->01");
	printf("\nSearch Employee ---->02");
	printf("\nDelete Employee ---->03");
	printf("\nSalary Report ---->04");
	printf("\nDisplay All Employee ---->05");
	printf("\nCount Employee ---->06");
	printf("\nUpdate Employee ---->07");
	
	printf("\nEnter Number :");
	scanf("%d",&option);
	
	switch(option){
		case 1:
			addEmployee();
			break;
		case 2:
			searchEmployee();
			break;
		case 3:
			deleteEmployee();
			break;
		case 4:
			getSalaryReport();
			break;
		case 5:
			displayAllEmployees();
			break;
		case 6:
			getEmployeeCount();
			break;
		case 7:
			updateEmployee();
			break;
		default:
			printf("\n\n\t\tEnter Above Number");
			printf("\n\n\t\t\tPress any key to Re enter.....");
			main();
		}
}


// Define the Employee structure
struct Employee{
    int id;
    char name[50];
    char department[50];
    float salary;
    int age;
};

// Function to add a new employee to the system
void addEmployee() {
    struct Employee e;
    FILE *fp = fopen("employees.txt", "a");
    printf("Enter employee ID: ");
    scanf("%d", &e.id);
    printf("Enter employee name: ");
    scanf("%s", e.name);
    printf("Enter employee department: ");
    scanf("%s", e.department);
    printf("Enter employee salary: ");
    scanf("%f", &e.salary);
    fprintf(fp, "%d %s %s %.2f\n", e.id, e.name, e.department, e.salary);
    fclose(fp);
}

// Function to display all employees in the system
void displayAllEmployees() {
    struct Employee e;
    FILE *fp = fopen("employees.txt", "r");
    printf("\nEmployees in the system:\n");
    printf("ID\tName\tDepartment\tSalary\n");
    while (fscanf(fp, "%d %s %s %f", &e.id, e.name, e.department, &e.salary) != EOF) {
        printf("%d\t%s\t%s\t%.2f\n", e.id, e.name, e.department, e.salary);
    }
    fclose(fp);
}

// Function to search for an employee by ID
void searchEmployee() {
    struct Employee e;
    int searchID;
    printf("\nEnter employee ID to search for: ");
    scanf("%d", &searchID);
    FILE *fp = fopen("employees.txt", "r");
    while (fscanf(fp, "%d %s %s %f", &e.id, e.name, e.department, &e.salary) != EOF) {
        if (e.id == searchID) {
            printf("\nEmployee found:\n");
            printf("ID: %d\n", e.id);
            printf("Name: %s\n", e.name);
            printf("Department: %s\n", e.department);
            printf("Salary: %.2f\n", e.salary);
            fclose(fp);
            return;
        }
    }
    printf("\nEmployee not found.\n");
    fclose(fp);
}

// Function to update an employee's information by ID
void updateEmployee(int id) {
  struct Employee emp;
  FILE *fp;

  fp = fopen("employees.dat", "rb+");
  if (fp == NULL) {
    printf("Error opening file");
    return;
  }

  while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
    if (emp.id == id) {
      printf("Enter new details for employee %d:\n", id);
      printf("Name: ");
      scanf("%s", emp.name);
      printf("Age: ");
      scanf("%d", &emp.age);
      printf("Salary: ");
      scanf("%f", &emp.salary);
      printf("Department: ");
      scanf("%s", emp.department);

      fseek(fp, -sizeof(struct Employee), SEEK_CUR);
      fwrite(&emp, sizeof(struct Employee), 1, fp);
      printf("Employee details updated successfully.\n");
      fclose(fp);
      return;
    }
  }

  printf("Employee with ID %d not found.\n", id);
  fclose(fp);
}

void deleteEmployee(int id) {
  struct Employee emp;
  FILE *fp, *temp;

  fp = fopen("employees.dat", "rb");
  if (fp == NULL) {
    printf("Error opening file");
    return;
  }

  temp = fopen("temp.dat", "wb");
  if (temp == NULL) {
    printf("Error opening file");
    return;
  }

  while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
    if (emp.id != id) {
      fwrite(&emp, sizeof(struct Employee), 1, temp);
    }
  }

  fclose(fp);
  fclose(temp);
  remove("employees.dat");
  rename("temp.dat", "employees.dat");
  printf("Employee with ID %d deleted successfully.\n", id);
}

void getSalaryReport() {
  struct Employee emp;
  FILE *fp;

  fp = fopen("employees.dat", "rb");
  if (fp == NULL) {
    printf("Error opening file");
    return;
  }

  float totalSalary = 0.0;

  printf("%-15s %-10s\n", "Employee Name", "Salary");
}

// Function to get the total number of employees in the system
int getEmployeeCount() {
    FILE *fp;
    int count = 0;
    char ch;
    
    // Open the file in read mode
    fp = fopen("employees.txt", "r");

    // If the file doesn't exist or is empty, return 0
    if (fp == NULL || feof(fp)) {
        return count;
    }
    
    // Count the number of lines in the file
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    
    // Close the file
    fclose(fp);
    
    // Return the total count of employees
    return count;
}
 

	
