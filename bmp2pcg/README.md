# bmp2pcg
16色のビットマップファイルからPCG用のアセンブラソースを生成するツール<br>

# 使用方法
bmp2pcg <in:BITMAP FILE NAME> <out:PATTERN FILE NAME> <out:COLOR FILE NAME> [START CHAR CODE] [START BLOCK NO]<br>
<br>
  <in:BITMAP FILE NAME>		入力するビットマップファイル名(256x192までの8の倍数のサイズ)<br>
  <out:PATTERN FILE NAME>	出力するパターンデータのアセンブラソースファイル名<br>
  <out:COLOR FILE NAME>		出力するカラーデータのアセンブラソースファイル名<br>
  [START CHAR CODE]			開始キャラクターコード(出力されるコメントにだけ影響)<br>
  [START BLOCK NO]			開始ブロックコード(出力されるコメントにだけ影響)<br>
<br>
ex.<br>
  bmp2pcg example.bmp example_pat.asm example_col.asm<br>
