# bmp2spbas
16色のビットマップファイルからスプライト用のBASICソースを生成するツール<br>

### 使用方法
bmp2spbas <in:BITMAP FILE NAME> <out:BASIC FILE NAME> [START ROW NUMBER] [INCLEMENTAL ROW NUMBER]<br>
<br>
  <in:BITMAP FILE NAME>		入力するビットマップファイル名<br>
  <out:PATTERN FILE NAME>	出力するパターンデータのアセンブラソースファイル名<br>
  <out:BASIC FILE NAME>		出力するBASICソースファイル名<br>
  [START ROW NUMBER]			開始行番号<br>
  [INCLEMENTAL ROW NUMBER]	行番号の増分<br>
<br>
ex.<br>
  bmp2spbas example.bmp example_sprite.bas 10000 10<br>

### 変更履歴
#### 2023.11.11
* 初版公開

![sprite_1](https://github.com/chikuwa-empire/msx-tool/assets/124578804/26111a5f-61e6-4635-b93e-1c4d9351d4fa)
![sprite_2](https://github.com/chikuwa-empire/msx-tool/assets/124578804/a011dcea-d6c6-4070-89da-8556d9be4b7e)
