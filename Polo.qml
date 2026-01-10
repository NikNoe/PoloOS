import QtQuick
import QtQuick3D

Node {
    id: node

    // --- STEP 1: Create an alias to the body material color ---
        // Change 'bodyMesh' to the actual ID of the car body model inside this file
        property alias bodyColor: bodyMaterial.baseColor

        Model {
            id: bodyMesh
            source: "meshes/car_body.mesh" // Your mesh path

            materials: [
                PrincipledMaterial {
                    id: bodyMaterial
                    baseColor: "black" // Default color
                    metalness: 0.6
                    roughness: 0.2
                }
            ]
        }

    // Resources
    Texture {
        id: undercarriage_PNG_texture
        objectName: "undercarriage.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/undercarriage.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/undercarriage.PNG
    }
    Texture {
        id: node6r_shiled_PNG_texture
        objectName: "6r_shiled.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_shiled.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_shiled.PNG
    }
    Texture {
        id: node6r_tire_PNG_texture
        objectName: "6r_tire.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_tire.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_tire.PNG
    }
    Texture {
        id: node6r_wheel_PNG_texture
        objectName: "6r_wheel.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_wheel.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_wheel.PNG
    }
    Texture {
        id: tsi_met4_PNG_texture
        objectName: "tsi_met4.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_met4.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_met4.PNG
    }
    Texture {
        id: node6r_glass1_PNG_texture
        objectName: "6r_glass1.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_glass1.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_glass1.PNG
    }
    Texture {
        id: node6r_dash_PNG_texture
        objectName: "6r_dash.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_dash.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_dash.PNG
    }
    Texture {
        id: bumper_frame_PNG_texture
        objectName: "bumper_frame.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/bumper_frame.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/bumper_frame.PNG
    }
    Texture {
        id: node6r_tex1_PNG_texture
        objectName: "6r_tex1.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_tex1.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_tex1.PNG
    }
    Texture {
        id: tsi_cbz_PNG_texture
        objectName: "tsi_cbz.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_cbz.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_cbz.PNG
    }
    Texture {
        id: tsi_met2_PNG_texture
        objectName: "tsi_met2.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_met2.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_met2.PNG
    }
    Texture {
        id: tsi_pulleys_PNG_texture
        objectName: "tsi_pulleys.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_pulleys.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_pulleys.PNG
    }
    Texture {
        id: tsi_tex2_PNG_texture
        objectName: "tsi_tex2.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_tex2.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_tex2.PNG
    }
    Texture {
        id: node6r_badge_PNG_texture
        objectName: "6r_badge.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_badge.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_badge.PNG
    }
    Texture {
        id: node6r_floor_PNG_texture
        objectName: "6r_floor.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_floor.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_floor.PNG
    }
    Texture {
        id: tsi_block_PNG_texture
        objectName: "tsi_block.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_block.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_block.PNG
    }
    Texture {
        id: node6r_headliner_PNG_texture
        objectName: "6r_headliner.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_headliner.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_headliner.PNG
    }
    Texture {
        id: node6r_cloth_PNG_texture
        objectName: "6r_cloth.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_cloth.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_cloth.PNG
    }
    Texture {
        id: nodamage_lod0_PNG_texture
        objectName: "nodamage_lod0.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/nodamage_lod0.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/nodamage_lod0.PNG
    }
    Texture {
        id: node6r_plastic2_PNG_texture
        objectName: "6r_plastic2.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_plastic2.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_plastic2.PNG
    }
    Texture {
        id: node6r_s_lod0_PNG_texture
        objectName: "6r_s_lod0.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_s_lod0.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_s_lod0.PNG
    }
    Texture {
        id: node6r_plastic_PNG_texture
        objectName: "6r_plastic.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_plastic.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_plastic.PNG
    }
    Texture {
        id: node6r_underbody_PNG_texture
        objectName: "6r_underbody.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_underbody.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_underbody.PNG
    }
    Texture {
        id: vehiclelights_PNG_texture
        objectName: "vehiclelights.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/vehiclelights.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/vehiclelights.PNG
    }
    Texture {
        id: node6r_bumper_frame_PNG_texture
        objectName: "6r_bumper_frame.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_bumper_frame.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_bumper_frame.PNG
    }
    Texture {
        id: node6r_red_PNG_texture
        objectName: "6r_red.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/6r_red.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/6r_red.PNG
    }
    Texture {
        id: tsi_tex1_PNG_texture
        objectName: "tsi_tex1.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/tsi_tex1.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/tsi_tex1.PNG
    }
    Texture {
        id: blackq_PNG_texture
        objectName: "blackq.PNG"
        generateMipmaps: true
        mipFilter: Texture.Linear
        // Source texture path expected: maps/blackq.PNG
        // Skipped property: source, reason: Failed to find texture at /Volumes/DJUMData/Tecnodjum/poloTDI/PoloOS/blackq.PNG
    }
    PrincipledMaterial {
        id: chassis_12_material
        objectName: "chassis.12"
        baseColor: "#ffe0e0e0"
        baseColorMap: node6r_shiled_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_21_material
        objectName: "chassis.21"
        baseColorMap: undercarriage_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_15_material
        objectName: "chassis.15"
        baseColorMap: tsi_tex1_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: glass_material
        objectName: "glass"
        baseColor: "#ff283435"
        roughness: 1
    }
    PrincipledMaterial {
        id: primary_001_material
        objectName: "primary.001"
        baseColor: "#ff3cff00"
        baseColorMap: node6r_bumper_frame_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_13_material
        objectName: "chassis.13"
        baseColorMap: node6r_red_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_18_material
        objectName: "chassis.18"
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_19_material
        objectName: "chassis.19"
        baseColor: "#ff3f3838"
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_22_material
        objectName: "chassis.22"
        baseColor: "#ff232323"
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_23_material
        objectName: "chassis.23"
        baseColor: "#ff868686"
        baseColorMap: node6r_shiled_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_24_material
        objectName: "chassis.24"
        baseColor: "#ffffb300"
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_25_material
        objectName: "chassis.25"
        roughness: 1
    }
    PrincipledMaterial {
        id: right_front_light_material
        objectName: "right front light"
        baseColor: "#ff00ffc8"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_10_material
        objectName: "chassis.10"
        baseColor: "#ffc0c0c0"
        roughness: 1
    }
    PrincipledMaterial {
        id: left_front_light_material
        objectName: "left front light"
        baseColor: "#ffffaf00"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_3_material
        objectName: "Imvlm lighting.3"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_10_material
        objectName: "Imvlm lighting.10"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_9_material
        objectName: "Imvlm lighting.9"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_4_material
        objectName: "Imvlm lighting.4"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_5_material
        objectName: "Imvlm lighting.5"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_6_material
        objectName: "Imvlm lighting.6"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_7_material
        objectName: "Imvlm lighting.7"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_8_material
        objectName: "Imvlm lighting.8"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: imvlm_lighting_2_material
        objectName: "Imvlm lighting.2"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_19_material
        objectName: "interior And engine.19"
        baseColorMap: node6r_plastic_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_20_material
        objectName: "chassis.20"
        baseColorMap: node6r_underbody_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_20_material
        objectName: "interior And engine.20"
        baseColorMap: node6r_plastic2_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_6_material
        objectName: "chassis.6"
        baseColorMap: node6r_s_lod0_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_21_material
        objectName: "interior And engine.21"
        baseColorMap: node6r_cloth_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_2_material
        objectName: "chassis.2"
        baseColorMap: nodamage_lod0_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_18_material
        objectName: "interior And engine.18"
        baseColorMap: node6r_headliner_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_5_material
        objectName: "chassis.5"
        baseColor: "#ffcf220a"
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_22_material
        objectName: "interior And engine.22"
        baseColorMap: node6r_floor_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_3_material
        objectName: "chassis.3"
        baseColorMap: tsi_block_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: glass_002_material
        objectName: "glass.002"
        baseColorMap: node6r_badge_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_8_material
        objectName: "chassis.8"
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_15_material
        objectName: "interior And engine.15"
        baseColorMap: tsi_pulleys_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_4_material
        objectName: "chassis.4"
        baseColorMap: tsi_tex2_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_16_material
        objectName: "interior And engine.16"
        baseColorMap: tsi_cbz_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_17_material
        objectName: "chassis.17"
        baseColorMap: tsi_met2_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: glass_001_material
        objectName: "glass.001"
        baseColor: "#ffdbe8df"
        roughness: 1
    }
    PrincipledMaterial {
        id: interior_And_engine_24_material
        objectName: "interior And engine.24"
        baseColorMap: bumper_frame_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_7_material
        objectName: "chassis.7"
        baseColorMap: node6r_tex1_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: glass_003_material
        objectName: "glass.003"
        baseColor: "#ffd3d3d3"
        baseColorMap: node6r_glass1_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_9_material
        objectName: "chassis.9"
        baseColorMap: node6r_dash_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: door_lf_ok_6_material
        objectName: "door_lf_ok.6"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: door_rf_ok_6_material
        objectName: "door_rf_ok.6"
        baseColorMap: vehiclelights_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: wheel_3_material
        objectName: "wheel.3"
        baseColorMap: node6r_wheel_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_1_material
        objectName: "chassis.1"
        baseColorMap: tsi_met4_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: wheel_4_material
        objectName: "wheel.4"
        baseColorMap: node6r_tire_PNG_texture
        roughness: 1
    }
    PrincipledMaterial {
        id: primary_material
        objectName: "primary"
        baseColor: "#ff3cff00"
        roughness: 1
    }
    PrincipledMaterial {
        id: chassis_16_material
        objectName: "chassis.16"
        baseColorMap: blackq_PNG_texture
        roughness: 1
    }

    // Nodes:
    Node {
        id: rootNode
        objectName: "RootNode"
        Node {
            id: polo
            objectName: "polo"
            position: Qt.vector3d(0, 75.7413, 0)
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            scale: Qt.vector3d(100, 100, 100)
            Node {
                id: chassis_dummy
                objectName: "chassis_dummy"
                Model {
                    id: chassis
                    objectName: "chassis"
                    position: Qt.vector3d(0, 0, -0.00145626)
                    source: "meshes/chassis_mesh.mesh"
                    materials: [
                        chassis_12_material,
                        primary_material,
                        chassis_1_material,
                        chassis_9_material,
                        chassis_7_material,
                        chassis_17_material,
                        chassis_4_material,
                        chassis_8_material,
                        chassis_3_material,
                        chassis_5_material,
                        chassis_2_material,
                        chassis_6_material,
                        chassis_20_material,
                        chassis_10_material,
                        chassis_13_material,
                        glass_material,
                        chassis_21_material,
                        chassis_16_material,
                        chassis_15_material,
                        primary_001_material,
                        chassis_18_material,
                        chassis_19_material,
                        chassis_22_material,
                        chassis_23_material,
                        chassis_24_material,
                        chassis_25_material
                    ]
                    Model {
                        id: imvlm_lighting
                        objectName: "Imvlm lighting"
                        source: "meshes/imvlm_lighting_mesh.mesh"
                        materials: [
                            right_front_light_material,
                            left_front_light_material,
                            imvlm_lighting_3_material,
                            imvlm_lighting_10_material,
                            imvlm_lighting_9_material,
                            imvlm_lighting_4_material,
                            imvlm_lighting_5_material,
                            imvlm_lighting_6_material,
                            imvlm_lighting_7_material,
                            imvlm_lighting_8_material,
                            imvlm_lighting_2_material
                        ]
                    }
                    Model {
                        id: interior_And_engine
                        objectName: "interior And engine"
                        source: "meshes/interior_And_engine_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_1_material,
                            chassis_9_material,
                            chassis_7_material,
                            chassis_17_material,
                            chassis_4_material,
                            chassis_8_material,
                            chassis_3_material,
                            chassis_6_material,
                            chassis_10_material,
                            chassis_21_material,
                            chassis_16_material,
                            chassis_15_material,
                            primary_001_material,
                            right_front_light_material,
                            interior_And_engine_19_material,
                            interior_And_engine_20_material,
                            interior_And_engine_21_material,
                            interior_And_engine_18_material,
                            interior_And_engine_22_material,
                            glass_002_material,
                            interior_And_engine_15_material,
                            interior_And_engine_16_material,
                            glass_001_material,
                            interior_And_engine_24_material
                        ]
                        Model {
                            id: glass_interior
                            objectName: "glass_interior"
                            position: Qt.vector3d(0.0355505, 0.280691, -0.554952)
                            source: "meshes/glass_interior_001_mesh.mesh"
                            materials: [
                                glass_material
                            ]
                        }
                    }
                    Node {
                        id: ug_nitro
                        objectName: "ug_nitro"
                        position: Qt.vector3d(0, -1.92967, 0.586852)
                    }
                    Model {
                        id: taillight_red_glass
                        objectName: "taillight_red_glass"
                        position: Qt.vector3d(0, 0, 0.00145626)
                        source: "meshes/taillight_red_glass_001_mesh.mesh"
                        materials: [
                            glass_003_material
                        ]
                    }
                }
                Node {
                    id: bonnet_dummy
                    objectName: "bonnet_dummy"
                    position: Qt.vector3d(0.000697272, 1.24049, 0.540249)
                    Model {
                        id: bonnet_ok
                        objectName: "bonnet_ok"
                        source: "meshes/bonnet_ok_001_mesh.mesh"
                        materials: [
                            primary_material
                        ]
                    }
                }
                Model {
                    id: boot_ok
                    objectName: "boot_ok"
                    position: Qt.vector3d(-0.00333014, -1.64004, 1.07971)
                    source: "meshes/boot_ok_mesh.mesh"
                    materials: [
                        primary_material,
                        chassis_1_material,
                        chassis_9_material,
                        chassis_8_material,
                        chassis_10_material,
                        interior_And_engine_19_material
                    ]
                    Model {
                        id: boot_ok_001
                        objectName: "boot_ok.001"
                        source: "meshes/boot_ok_003_mesh.mesh"
                        materials: [
                            glass_material
                        ]
                    }
                }
                Node {
                    id: bump_front_dummy
                    objectName: "bump_front_dummy"
                    position: Qt.vector3d(1.08917, 1.94019, 0.0497288)
                    Model {
                        id: bumper_front_ok
                        objectName: "bumper_front_ok"
                        source: "meshes/bumper_front_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_1_material,
                            chassis_9_material,
                            chassis_7_material,
                            chassis_10_material
                        ]
                    }
                }
                Node {
                    id: bump_rear_dummy
                    objectName: "bump_rear_dummy"
                    position: Qt.vector3d(1.07499, -1.82025, 0.0798925)
                    Model {
                        id: bump_rear_ok
                        objectName: "bump_rear_ok"
                        source: "meshes/bump_rear_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_7_material
                        ]
                    }
                }
                Node {
                    id: door_lr_dummy
                    objectName: "door_lr_dummy"
                    position: Qt.vector3d(-1.02982, -0.285114, 0.176041)
                    Model {
                        id: door_lr_ok
                        objectName: "door_lr_ok"
                        source: "meshes/door_lr_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_7_material,
                            chassis_10_material,
                            glass_material,
                            interior_And_engine_19_material,
                            interior_And_engine_20_material
                        ]
                    }
                }
                Node {
                    id: door_lf_dummy
                    objectName: "door_lf_dummy"
                    position: Qt.vector3d(-1.02983, 1.0346, 0.17603)
                    Model {
                        id: door_lf_ok
                        objectName: "door_lf_ok"
                        source: "meshes/door_lf_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_1_material,
                            chassis_7_material,
                            chassis_10_material,
                            interior_And_engine_19_material,
                            interior_And_engine_20_material,
                            door_lf_ok_6_material
                        ]
                        Model {
                            id: door_lf_ok_001
                            objectName: "door_lf_ok.001"
                            source: "meshes/door_lf_ok_003_mesh.mesh"
                            materials: [
                                glass_material
                            ]
                        }
                    }
                }
                Node {
                    id: wing_lf_dummy
                    objectName: "wing_lf_dummy"
                    position: Qt.vector3d(-1.02983, 1.5647, 0.17603)
                    Model {
                        id: wing_lf_ok
                        objectName: "wing_lf_ok"
                        source: "meshes/wing_lf_ok_001_mesh.mesh"
                        materials: [
                            primary_material
                        ]
                    }
                }
                Node {
                    id: wing_rf_dummy
                    objectName: "wing_rf_dummy"
                    position: Qt.vector3d(1.03, 1.5647, 0.17603)
                    Model {
                        id: wing_rf_ok
                        objectName: "wing_rf_ok"
                        source: "meshes/wing_rf_ok_001_mesh.mesh"
                        materials: [
                            primary_material
                        ]
                    }
                }
                Node {
                    id: door_rf_dummy
                    objectName: "door_rf_dummy"
                    position: Qt.vector3d(1.03, 1.0346, 0.17603)
                    Model {
                        id: door_rf_ok
                        objectName: "door_rf_ok"
                        source: "meshes/door_rf_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_1_material,
                            chassis_7_material,
                            chassis_10_material,
                            interior_And_engine_19_material,
                            interior_And_engine_20_material,
                            door_rf_ok_6_material
                        ]
                        Model {
                            id: door_rf_ok_001
                            objectName: "door_rf_ok.001"
                            source: "meshes/door_rf_ok_003_mesh.mesh"
                            materials: [
                                glass_material
                            ]
                        }
                    }
                }
                Node {
                    id: door_rr_dummy
                    objectName: "door_rr_dummy"
                    position: Qt.vector3d(1.03, -0.285114, 0.176041)
                    Model {
                        id: door_rr_ok
                        objectName: "door_rr_ok"
                        source: "meshes/door_rr_ok_mesh.mesh"
                        materials: [
                            primary_material,
                            chassis_1_material,
                            chassis_7_material,
                            chassis_10_material,
                            glass_material,
                            interior_And_engine_19_material,
                            interior_And_engine_20_material
                        ]
                    }
                }
                Node {
                    id: windscreen_dummy
                    objectName: "windscreen_dummy"
                    position: Qt.vector3d(0.000697258, 0.900069, 0.791289)
                    Model {
                        id: windscreen_ok
                        objectName: "windscreen_ok"
                        source: "meshes/windscreen_ok_001_mesh.mesh"
                        materials: [
                            glass_material
                        ]
                    }
                }
                Node {
                    id: steering_dummy
                    objectName: "steering_dummy"
                    position: Qt.vector3d(-0.421174, 0.501787, 0.464729)
                    rotation: Qt.quaternion(0.98063, -0.195868, 0, 0)
                    scale: Qt.vector3d(1, 1, 1)
                    Model {
                        id: steering_ok
                        objectName: "steering_ok"
                        source: "meshes/steering_ok_mesh.mesh"
                        materials: [
                            chassis_7_material,
                            chassis_10_material,
                            right_front_light_material,
                            interior_And_engine_19_material,
                            glass_002_material
                        ]
                    }
                }
                Node {
                    id: speedo_dummy
                    objectName: "speedo_dummy"
                    position: Qt.vector3d(-0.433826, 0.812953, 0.466932)
                    rotation: Qt.quaternion(0.988756, -0.149538, 0, 0)
                    Model {
                        id: speedook
                        objectName: "speedook"
                        position: Qt.vector3d(0.125823, 0.00758165, 0.00265263)
                        rotation: Qt.quaternion(0.999989, 0.00462517, 0, 0)
                        source: "meshes/speedook_mesh.mesh"
                        materials: [
                            chassis_9_material,
                            interior_And_engine_19_material
                        ]
                    }
                    Model {
                        id: tahook
                        objectName: "tahook"
                        position: Qt.vector3d(-0.0995512, -5.96046e-08, -4.47035e-08)
                        source: "meshes/tahook_mesh.mesh"
                        materials: [
                            chassis_9_material,
                            interior_And_engine_19_material
                        ]
                    }
                }
                Node {
                    id: other_dummy
                    objectName: "other_dummy"
                    position: Qt.vector3d(0, 0, -0.00145626)
                    Node {
                        id: node1ventila_dummy_
                        objectName: "1ventila_dummy "
                        position: Qt.vector3d(0.195628, 2.33871, -0.252497)
                        Model {
                            id: vent
                            objectName: "vent"
                            source: "meshes/vent_001_mesh.mesh"
                            materials: [
                                chassis_1_material
                            ]
                        }
                    }
                }
                Node {
                    id: kabina_dummy
                    objectName: "kabina_dummy"
                    position: Qt.vector3d(-0.00396726, -1.60266, 0.0300991)
                    Model {
                        id: chassis_001
                        objectName: "chassis.001"
                        source: "meshes/chassis_003_mesh.mesh"
                        materials: [
                            interior_And_engine_22_material
                        ]
                    }
                }
            }
            Node {
                id: wheel_rf_dummy
                objectName: "wheel_rf_dummy"
                position: Qt.vector3d(0.91, 1.59581, -0.343143)
                Model {
                    id: wheel
                    objectName: "wheel"
                    position: Qt.vector3d(0.0412046, 0, -0.0185421)
                    scale: Qt.vector3d(0.829655, 1.07044, 1.07044)
                    source: "meshes/wheel_mesh.mesh"
                    materials: [
                        chassis_1_material,
                        chassis_7_material,
                        chassis_10_material,
                        wheel_3_material,
                        wheel_4_material
                    ]
                }
                Model {
                    id: wheel_001
                    objectName: "wheel.001"
                    position: Qt.vector3d(0.0412046, -3.23363, -0.0185421)
                    scale: Qt.vector3d(0.829655, 1.07044, 1.07044)
                    source: "meshes/wheel_001_mesh.mesh"
                    materials: [
                        chassis_1_material,
                        chassis_7_material,
                        chassis_10_material,
                        wheel_3_material,
                        wheel_4_material
                    ]
                }
                Model {
                    id: wheel_002
                    objectName: "wheel.002"
                    position: Qt.vector3d(-1.8615, -3.23363, -0.0185421)
                    rotation: Qt.quaternion(-4.37114e-08, 1, 0, 0)
                    scale: Qt.vector3d(-0.829655, -1.07044, -1.07044)
                    source: "meshes/wheel_002_mesh.mesh"
                    materials: [
                        chassis_1_material,
                        chassis_7_material,
                        chassis_10_material,
                        wheel_3_material,
                        wheel_4_material
                    ]
                }
                Model {
                    id: wheel_003
                    objectName: "wheel.003"
                    position: Qt.vector3d(-1.8615, 0, -0.0185421)
                    rotation: Qt.quaternion(-4.37114e-08, 1, 0, 0)
                    scale: Qt.vector3d(-0.829655, -1.07044, -1.07044)
                    source: "meshes/wheel_003_mesh.mesh"
                    materials: [
                        chassis_1_material,
                        chassis_7_material,
                        chassis_10_material,
                        wheel_3_material,
                        wheel_4_material
                    ]
                }
            }
        }
    }

    // Animations:
}
