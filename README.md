# Mx2D
Учебный проект. Моделирование движения тел на плоскости (2D физический движок).

## Части

1. Графика
2. Геометрия
3. Механика
  * Движение твёрдого тела под действием сил (без прямого учёта связей).
  * Возможность задавать поля сил в областях.
  * Учёт трения скольжения (и момента трения качения -- круги?).
  * Удар с коэффициентом восстановления.

## Рассуждения

### Пример "колесо"

1. Колесо массы $m$ и радиуса $r$, момента инерции $J$ движется без отрыва от поверхности и без проскальзывания (три координаты и две связи).
2. Центр масс совпадает с геометрическим центром.
3. К центру масс приложена внешняя активная сила $F$ (если требуется, включает силу веса).
4. К колесу приложен внешний активный момент $M$.

Система:

```math
\left\{\begin{array}{ccc}
m\ddot{x} & = & F_x + R_x,\\
m\ddot{y} & = & F_y + R_y,\\
J\ddot{\varphi} & = & M + R_\varphi,\\
y & = & r,\\
x & = & r\varphi.
\end{array}\right.
```

Силы реакций $R_x$, $R_y$, $R_\varphi$ не известны.

Если продифференцировать уравнения связей, получим дополнительные условия на производные:

```math
\left\{\begin{array}{ccc}
\ddot{y} & = & 0,\\
\ddot{x} & = & r\ddot{\varphi},
\end{array}\right.
```

из первого получим: $R_y = -F_y$.
Подставив второе в систему, получим:

```math
\left\{\begin{array}{ccc}
m\ddot{x} & = & F_x + R_x,\\
J\ddot{x} & = & r M + r R_\varphi,
\end{array}\right.
```

т.е. $J(F_x + R_x) = m r(M + R_\varphi)$ или

```math
J R_x + m r R_\varphi = m r M - J F_x,
```

что пока сохраняет неоднозначность.

Выпишем минимальное решение через псевдообращение:

```math
\left\{\begin{array}{ccc}
R_x & = & \dfrac{J}{J^2 + m^2 r^2}\left(m r M - J F_x\right),\\
R_\varphi & = & \dfrac{m r}{J^2 + m^2 r^2}\left(m r M - J F_x\right),
\end{array}\right.
```

Подставим это решение в уравнение относительно $\ddot{x}$:

```math
\ddot{x} = \dfrac{m r^2 F_x + \dfrac{J r}{m} M}{J^2 + m^2 r^2},
```

откуда:

```math
x = \dfrac{m r^2 F_x + \dfrac{J r}{m} M}{J^2 + m^2 r^2}\dfrac{t^2}{2} + \dot{x}_0 t + x_0.
```

### Обобщение

- q — вектор состояния системы
- v — вектор скоростей
- w — вектор ускорений
- R — вектор неизвестных реакций
- Q — вектор нормированных сил
- A — функция связей

Метод средней точки:

```math
\left\{\begin{array}{cclccc}
\dot{q} & = & v & \Rightarrow & q & \approx & w\dfrac{1}{2}h^2 + v_0 h + q_0,\\
\dot{v} & = & w & \Rightarrow & v & \approx & w h + v_0,\\
w & = & Q\left(t + \frac{1}{2}h, \frac{1}{2}(q_0 + q), \frac{1}{2}(v_0 + v)\right) + R,\\
0 & = & A(t + \frac{1}{2}h, \frac{1}{2}(q_0 + q), \frac{1}{2}(v_0 + v)).
\end{array}\right.
```

dim A < dim w = dim R => R определяется неоднозначно

```math
A(t, q, v) = 0 \Rightarrow\\
\dot{A} = \dfrac{\partial A}{\partial t}(t, q, v) + \dfrac{\partial A}{\partial q}(t, q, v) v + \dfrac{\partial A}{\partial v}(t, q, v) w = 0.
```

Приходим к недоопределённой системе относительно $w$ и $R$ (для метода средней точки):

```math
\left\{\begin{array}{ccl}
t_{0.5} & = & t_0 + \frac{1}{2}h,\\
v_{0.5} & = & v_0 + \frac{h}{2}w,\\
q_{0.5} & = & q_0 + \frac{h}{2}v_0 + \dfrac{h^2}{4}w,\\
w - R & = & Q\left(t_{0.5}, q_{0.5}, v_{0.5}\right),\\
\dfrac{\partial A}{\partial v}\left(t_{0.5}, q_{0.5}, v_{0.5}\right) w & = 
& -\dfrac{\partial A}{\partial t}\left(t_{0.5}, q_{0.5}, v_{0.5}\right) - \dfrac{\partial A}{\partial q}\left(t_{0.5}, q_{0.5}, v_{0.5}\right) v_{0.5}.
\end{array}\right.
```

Если продифференцировать уравнения связей:

```math
\left\{\begin{array}{rclr}
\mathbf M \ddot{\mathbf x} & = & \mathbf{F}(t, \mathbf x, \dot{\mathbf x}) + \mathbf{R}, & \mathbf x \in \mathbb R^n, \mathbf R \in \mathbb R^n,\\
\mathbf A(t, \mathbf x, \dot{\mathbf x}) \ddot{\mathbf x} & = & \mathbf a(t, \mathbf x, \dot{\mathbf x}), & \mathbf A(t, \mathbf x, \dot{\mathbf x}) \in \mathbb R^{s \times n}.
\end{array}\right.
```

Поскольку $s < n$, то система с $2n$ уравнений недоопределена.
