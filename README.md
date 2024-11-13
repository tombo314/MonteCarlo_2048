## 「2048」というスマホゲームの攻略です

MCTSのノードの展開を1層にしたものです。複数階層にした方が強いかもしれません。

以下のアルゴリズムが使われています。
- UCT
- モンテカルロ法
- 貪欲法

### UCT
UCTは Upper Confidence Bound 1 applied to Trees のような感じの略で（表記ゆれが多そう）、ucb1のアルゴリズムをモンテカルロ木探索に応用したものです。詳しくはコードを見てください。

### 貪欲法
下の次に左右、合成の次に詰めるという優先順序で貪欲にプレイアウトしています。インプットは乱択です。

### 記録
自分の人力では26884点、モンテカルロの通りに動かしていったら34664点で終わりました。人力、アルゴリズムの両方で記録の更新を頑張ってください。アルゴリズムが改善したら教えてください。

### 自動化したい
手作業が大変なので、自動でスマホを操作できるといいなーと思ってます。

### AHC015
AHC015の復習のコードをもとに改変したもので、一部コメントなどが残っています