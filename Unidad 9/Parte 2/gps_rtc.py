import time
from datetime import datetime, timedelta, timezone


def gps_time():
    # Definir la fecha de inicio del tiempo GPS
    gps_epoch = datetime(1980, 1, 6, 0, 0, 0, tzinfo=timezone.utc)

    # Obtener la hora actual en UTC
    now = datetime.now(timezone.utc)

    # Calcular la diferencia en segundos entre ahora y la época GPS
    delta = now - gps_epoch
    total_seconds = delta.total_seconds()

    # Calcular el número de semanas y los segundos dentro de la semana
    gps_weeks = int(total_seconds // (7 * 24 * 3600))
    gps_seconds = int(total_seconds % (7 * 24 * 3600))

    # La diferencia actual entre GPS y UTC es de 18 segundos
    gps_seconds += 18

    return gps_weeks, gps_seconds


def hardware_time():
    # Obtener la hora del sistema en segundos desde la época
    return int(time.time())


def gps_to_utc(gps_weeks, gps_seconds):
    # Definir la fecha de inicio del tiempo GPS
    gps_epoch = datetime(1980, 1, 6, 0, 0, 0, tzinfo=timezone.utc)

    # Calcular el número total de segundos desde la época GPS
    total_seconds = gps_weeks * 7 * 24 * 3600 + gps_seconds

    # Ajustar por la diferencia entre GPS y UTC (18 segundos)
    total_seconds -= 18

    # Calcular la fecha y hora UTC
    utc_time = gps_epoch + timedelta(seconds=total_seconds)

    return utc_time


# Obtener la hora GPS actual
gps_weeks, gps_seconds = gps_time()
print(f"Semana GPS: {gps_weeks}, Segundos de la semana: {gps_seconds}")

# Obtener la hora del sistema
system_time = hardware_time()
print(f"Hora del sistema: {system_time}")

# Convertir la hora GPS actual a UTC
gps_utc = gps_to_utc(gps_weeks, gps_seconds)
print("Hora UTC desde GPS:", gps_utc)

# Convertir la hora del sistema a UTC
system_utc = datetime.fromtimestamp(system_time, timezone.utc)
print("Hora UTC desde el sistema:", system_utc)

# Calcular la diferencia entre la hora GPS actual y la hora del sistema
difference = gps_utc - system_utc
print("Diferencia entre la hora GPS actual y la hora del sistema:", difference)
