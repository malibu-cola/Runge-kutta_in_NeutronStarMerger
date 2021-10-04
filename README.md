# Runge-kutta_in_NeutronStarMerger

- syoki_RK.cpp を実行し、初期条件を各々入力すると、計算に必要な定数と、時間に対する半径の変化がtxtfileで出力される。それをR_t.pltを実行（terminal上で"gnuplot R_t.plt"）すると時間に対する半径の変化のグラフが得られる。


## 概要

$$
\frac{d^2 R}{dt^2} \sim -\frac{4 \pi G \rho R}{3} + \frac{3 \gamma P}{\rho R} + R (\tau_{exp} + \frac{3}{2} t)^{-2}
$$
について、密度や圧力$V_{exp}$がこの値の時に$R$がこれくらいという図を作りたい

$$
\frac{d^2 R}{dt^2} \sim -\frac{4 \pi}{3} G \rho_0 R_0^3 (R(t))^{-2}+3\gamma K \rho_0^{\gamma -1} R_0^{3(\gamma -1)} (R(t))^{-3\gamma +2} +(\tau_{exp} + \frac{3}{2})^{-2} R(t)
$$
と変形できるので
$$
\frac{d^2 x}{dt^2} =Ax^{-2} +B x^{-4} +(C + \frac{3}{2}t)^{-2} x
$$
$$
A=-\frac{4 \pi}{3} G \rho_0 R_0^3,
$$
$$
B=3\gamma K \rho_0^{\gamma -1} R_0^{3(\gamma -1)} ,
$$
$$
C=\tau_{exp} =\frac{r_c}{V_{exp}}
$$
としてルンゲクッタ法で方程式を解く。


## ルンゲクッタ法とは

関数$x=x(t)$に対して、微分方程式$\frac{dx}{dt} =f(t,x)$が定義されているとする。tの刻み幅をh、現在の時刻を$t_i$、次の時刻を$t_{i+1}=t_i +h$とする。

ルンゲクッタ法では微小時間$h$経過後の関数の値$x_{i+1}$を
$$
x_{i+1} = x_i+k, k=\frac{h}{6} (k_0 + 2k_{1} + 2k_{2} +k_3)
$$
として算出する。
ここで$k_0 ~ k_3$はそれぞれ、
$$
k_0 =f(t_i, x_i)
$$
$$
k_1 =f(t_i + \frac{h}{2}, x_i +k_0 \frac{h}{2})
$$
$$
k_2 =f(t_i +\frac{h}{2}, x_i + k_1\frac{h}{2})
$$
$$
k_3 =f(t_i +h, x_i + k_2 h)
$$
である。
今回は二階微分方程式なので、$y=dx/dt$として、
$$
\frac{dy}{dt} =f(x,y,t)
$$
$$
\frac{dx}{dt} =y
$$
として連立して解いた。
