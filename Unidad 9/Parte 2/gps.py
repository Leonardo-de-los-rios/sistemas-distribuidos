from datetime import datetime, timezone


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


# Obtener la hora GPS actual
weeks, seconds = gps_time()
print(f"Semana GPS: {weeks}, Segundos de la semana: {seconds}")
