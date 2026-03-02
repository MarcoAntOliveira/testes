import subprocess
import json
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation  # ← IMPORT CORRETO
from collections import deque
import time

energia_vals = deque(maxlen=500)
tempo_vals = deque(maxlen=500)
start_time = time.time()

# Impulso inicial na esfera
impulso = [0, 0, -2.0]

cmd_velocity = [
    "gz", "topic", "-et", "/model/sphere/command/motor_speed",
    "-m", "gz.msgs.Vector3d",
    "-p", f"x:{impulso[0]} y:{impulso[1]} z:{impulso[2]}"
]
subprocess.run(cmd_velocity)

# Lê energia cinética em stream
cmd_topic = ["gz", "topic", "-et", "/model/sphere/kinetic_energy"]
process = subprocess.Popen(cmd_topic, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

fig, ax = plt.subplots()
line, = ax.plot([], [], lw=2)
ax.set_title("Energia Cinética em Tempo Real")
ax.set_xlabel("Tempo (s)")
ax.set_ylabel("Energia (J)")
ax.grid(True)

def update(frame):
    while True:
        line_data = process.stdout.readline()
        if not line_data:
            break
        try:
            msg = json.loads(line_data)
            energia = msg["data"][0]
            tempo = time.time() - start_time
            energia_vals.append(energia)
            tempo_vals.append(tempo)
            print(f"[{tempo:.2f} s] Energia cinética: {energia:.4f} J")
        except Exception:
            continue

    line.set_data(tempo_vals, energia_vals)
    ax.relim()
    ax.autoscale_view()
    return line,

ani = FuncAnimation(fig, update, interval=100, cache_frame_data=False)  # ← CORREÇÃO AQUI
plt.show()
