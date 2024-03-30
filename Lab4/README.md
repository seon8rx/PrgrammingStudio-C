### [Lab4] C Mini Project

프로그래밍스튜디오 01분반 22100110 김성규

---
<웹사이트 회원의 기본 정보 목록 관리>

CRUD를 이용할 수 있고 기능을 구현할 수 있을 수준에서 모델을 살펴보던 중 struct, struct* 등 지난 과제들에서 복습한 내용을 다시 활용할 수 있는 주제이며, 회원의 id와 pw에서 pw를 *로 가려서 출력하는 부분을 구현해 보고 싶어서 정하게 되었습니다.

int createData(Member* m[]);<br>
프로그램을 시작하며 member_list.txt 파일에 있는 내용을 읽어와서 main.c의 int no에 총 몇명의 회원의 정보를 읽어 왔는지를 리턴한다.<br>
void readMembers(Member* m[], int size);<br>
구조체 배열에 동적으로 받아온 정보들을 출력한다. 이때 회원의 비밀번호는 문자열로 이루어져 있고, 문자열의 수(비밀번호의 길이)만큼 \* 로 출력한다.<br>
void updateMember(Member* m[], int size);<br>
몇번째의 회원의 정보를 수정할지 입력 받아 범위 내의 있는지를 확인하고 범위 밖일 경우 잘못됐다는 메세지를 출력한다. 범위 내일 경우 각각의 정보들을 수정한다.<br>
int deleteMember(Member* m[], int size);<br>
update와 동일하게 몇번째의 회원의 정보를 수정할지 입력을 받고 범위 안에 있는 번호인지 확인하고, 범위 밖일 경우 잘못됨을 출력한다. 범위 안일 경우 선택한 회원의 정보를 출력하고, 삭제 확인을 받은 후 no를 선택할 경우 취소를, yes를 선택한 경우 해당 회원의 정보를 삭제하고 해당 회원의 정보 뒤에 있던 내용을 한칸씩 당긴다. 리턴 값으로 전체 size에서 1을 빼고 리턴한다. 잘못된 번호를 선택하거나 취소할 경우 size값을 그대로 다시 리턴한다.<br>
void provideInfo(Member* m[], int i);<br>
search, update, delete에서 동일한 방식으로 회원 한명의 정보를 출력한는 경우를 발견하여 추가적으로 index값을 받아와 해당 index의 정보를 출력하는 함수를 구현하였다.<br>
void searchMember(Member* m[], int size);<br>
(1:by name, 2:by age, 3:by gender)로 3개의 선택지를 주고 어떠한 내용으로 검색을할지 입력받는다. 1,2,3외의 값을 입력 받으면 option에 없는 내용이라는 내용을 출력하고, 1,2,3을 입력받으면 string, int, gender (1:MALE , 2:FEMALE)를 입력 받아 구조체 배열을 반복문으로 훑으며 입력 받은 내용을 가지고 있는 회원의 정보를 출력한다.<br>
void saveInfo(Member* m[], int size);<br>
기존에 프로그램을 실행할 때 사용했던 (createData) 텍스트 파일에 동일한 양식으로 이름, 나이, 성별(0 or 1), email, password를 입력하고 파일을 닫는다.<br>
void makeReport(Member* m[], int size);<br>
saveInfo와 동일하게 파일에 내용을 입력하는 함수이지만, 새롭게 report.txt파일에 비밀번호는 \*인 상태로 출력하고, 회원들의 총 인원수, 평균연령, 남자 회원 수, 남자 회원의 평균 연령, 여자 회원 수, 여자 회원의 평균 연령을 계산하여 같이 파일에 출력한다.<br>
void pickupRandomMember(Member* m[], int size);<br>
몇명의 회원 정보를 random으로 출력할 것인지 입력을 받고, size의 범위를 벗어 낫을 경우 잘못되었다는 내용을 출력하고, 범위 내의 int 값을 받았을 경우 해당 수 만큼 무작위 회원의 정보를 출력한다.<br>
int addNewMember(Member* m[], int size);<br>
추가적으로 만든 함수이며 목록에 새로운 회원의 정보를 추가하는 기능을 가졌다. 동적으로 할당 받아 새로운 회원의 정보를 입력 받고 구조체 배열로 받은 제일 마지막 위치에 저장하며 리턴값으로는 size값을 +1하여 리턴한다.<br>

---
make.png는 make를 이용하여 컴파일하고 프로그램을 실행시킨 이미지 입니다.<br>
create.png, read.png는 프로그램을 실행하며 createData로 파일을 읽어오고 1번 선택지로 화면에 읽어온 회원 정보를 출력한 이미지 입니다.<br>
update.png는 회원의 정보를 수정하는 이미지로, 잘못된 값을 받았을 때 입력 값이 잘못 되었다는 메세지 출력 예시도 포함하고 있습니다.<br>
delete.png는 회원의 정보를 삭제하는 이미지로, 잘못된 값을 받았을 때 입력 값이 잘못 되었다는 메세지 출력 예시도 포함하고 있으며, 취소했을 경우도 포함하고 있습니다. 성공적으로 삭제 시 목록 출력 화면을 기준으로 해당 위치의 정보 보다 아래의 정보들을 한칸씩 위로 올렸습니다.<br>
search.png는 회원의 정보를 검색하는 이미지로 3개의 선택지가 있고, 3개의 선택지 외의 값을 입력하면 입력 값이 잘못 되었다는 메세지를 출력합니다. 내용을 찾을 경우 해당 정보를 가진 회원의 정보를 출력합니다.<br>
save.png와 save_result.png는 프로그램을 실행하며 읽어왔던 동일한 텍스트 파일에 첫 양식에 맞추어 수정된 내용을 저장하는 이미지 입니다.<br>
report.png와 report_result는 프로그램 실행 중 출력하던 양식으로 report.txt 파일에 출력하며 총 회원의 수와 남자, 여자 회원의 수 그리고 각각의 평균 연령 또한 계산하여 출력된 이미지 입니다.<br>
randomMember.png는 범위내의 숫자로 입력값을 받고 해당 숫자만큼 무작위 회원의 정보를 출력하는 실행장면의 이미지 입니다. 범위 외의 입력 값을 받으면 잘못되었다는 메세지를 출력합니다.<br>
add.png는 새로운 회원의 정보를 입력받아 목록의 제일 마지막에 해당 회원의 정보를 받아 제일 마지막에 출력되는 이미지 입니다.<br>

---
막상 crud기능을 가진 프로그램을 혼자 처음부터 만들어야한다는 생각에 갑갑했지만, 이전 과제들을 토대로 하나씩 구현해 나갈 수 있었다. 하지만 라이브러리 파일을 두개 이상 사용해서 하나의 main.c를 실행시키는 부분은 아직 몰라서 이번 과제에서 적용하지 못했고 그부분에 아쉬움이 많이 남아있다.