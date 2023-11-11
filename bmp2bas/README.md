# bmp2bas
16色のビットマップファイルからPCG用のBASIC DATA文ソースを生成するツール<br>

### 使用方法
bmp2bas <in:BITMAP FILE NAME> <out:BASIC FILE NAME> [START ROW NUMBER] [INCLEMENTAL ROW NUMBER] [START CHAR CODE]<br>
<br>
<in:BITMAP FILE NAME>		入力するビットマップファイル名(256x192までの8の倍数のサイズ)<br>
<out:BASIC FILE NAME>		出力するBASICのソースファイル名<br>
[START ROW NUMBER]			開始行番号<br>
[INCLEMENTAL ROW NUMBER]	行番号の増分<br>
[START CHAR CODE]			開始キャラクターコード(コメントに出力)<br>
<br>
ex.<br>
  bmp2bas example.bmp example.bas 10000 10 96

### 変更履歴
#### 2023.11.11
* 初版公開。

![pcgmake1](https://github.com/chikuwa-empire/msx-tool/assets/124578804/014339e7-fc16-45c2-8cc5-7ec0e545675c)
![pcgmake2](https://github.com/chikuwa-empire/msx-tool/assets/124578804/11f070aa-311b-4947-be78-63eee4fd4aa3)
