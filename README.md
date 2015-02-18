# Remote-Aircon-Controll-with-Arduino-Twitter-Node.js-Raspberry-Pi
エアコンの遠隔操作をラズパイとArduinoとTwitter Streaming APIとで連携して行います

※ほぼ自分用のメモですので、文章がすべてわかりづらいと思います。
Arduinoで赤外線を読み取るコードはRead_IRにあります。赤外線のHighとLowのときの時間をシリアルモニタに出力します。
時間間隔を使って0, 1を表しているので、その変換をmake_signal.plが行います。avg_signal.plは時間間隔の平均を算出します。
Arudinoに焼き付けるコードは「Node_IR_Sending」にあります。
twitter_iot.jsはNode.jsで実行するコードです。必要なモジュールは「twitter, serialport, socket.io」です

