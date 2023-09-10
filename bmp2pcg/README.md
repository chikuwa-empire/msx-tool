# bmp2pcg
16色のビットマップファイルからPCG用のアセンブラソースを生成するツール<br>

### 使用方法
bmp2pcg <in:BITMAP FILE NAME> <out:PATTERN FILE NAME> <out:COLOR FILE NAME> [START CHAR CODE] [START BLOCK NO]<br>
<br>
  <in:BITMAP FILE NAME>		入力するビットマップファイル名<br>
  <out:PATTERN FILE NAME>	出力するパターンデータのアセンブラソースファイル名<br>
  <out:COLOR FILE NAME>		出力するカラーデータのアセンブラソースファイル名<br>
  [START CHAR CODE]			開始キャラクターコード(出力されるコメントにだけ影響)<br>
  [START BLOCK NO]			開始ブロックコード(出力されるコメントにだけ影響)<br>
<br>
ex.<br>
  bmp2pcg example.bmp example_pat.asm example_col.asm<br>

### 変更履歴
#### 2023.06.07
* 画像の大きさの制限をやめました。8の倍数かどうかだけチェックしてます。
* DONE.に改行を入れ忘れてました。

![pcgmake1](https://github.com/chikuwa-empire/msx-tool/assets/124578804/9b57f2cb-fc09-4d6b-91dc-75b0fa702bf8)
![pcgmake2](https://github.com/chikuwa-empire/msx-tool/assets/124578804/5ea5ee40-cfd3-45f6-a5a2-c0ce6896fd33)
![pcgmake3](https://github.com/chikuwa-empire/msx-tool/assets/124578804/368a2771-e35d-4964-a3f5-8ed539e37707)
