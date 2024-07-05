import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from ..bme680_bsec import to_code_base, CONFIG_SCHEMA_BASE

AUTO_LOAD = ["bme680_bsec"]
CODEOWNERS = ["@apbodrov"]
DEPENDENCIES = ["spi"]


bme680_spi_ns = cg.esphome_ns.namespace("bme680_spi")
bme680SPIComponent = bme680_spi_ns.class_(
    "bme680SPIComponent", cg.PollingComponent, spi.SPIDevice
)

CONFIG_SCHEMA = CONFIG_SCHEMA_BASE.extend(spi.spi_device_schema()).extend(
    {cv.GenerateID(): cv.declare_id(bme680SPIComponent)}
)


async def to_code(config):
    var = await to_code_base(config)
    await spi.register_spi_device(var, config)
