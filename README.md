# CSE100_Project_2
<br />
"Actor Graph"는 Marconi가 주장한 "이 세상의 모든 사람이 여섯 명만 건너면 서로 알고 있다"을 인용하여 영화배우들의 연결 고리를 찾는 프로젝트입니다.
<br />

https://drive.google.com/file/d/1c8_Bdpz7MGaeRpMwnKIZ9U1s5V20CLOr/view?usp=sharing
<br />
BFS algorithm을 이용하여 위 링크에 있는 데이터를 바탕으로 아래와 같은 형식의 Actor graph를 만듭니다.
<br />
(배우이름)--[영화제목#@연도]-->(배우)
<br />
예시는 아래와 같습니다.
<br />
ex1)<br />
(Robert Downey Jr.)--[Avengers: Age of Ultron#@2015]-->(Chris Evans)<br />
ex2)<br />
(Amy Adams)--[Leap Year#@2010]-->(Matthew Goode)--[Stoker#@2013]-->(Nicole Kidman)